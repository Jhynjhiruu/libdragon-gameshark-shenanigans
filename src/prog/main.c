#include <libdragon.h>

uint8_t rombuf[0x4000 + 0x29] = {0};

static uint8_t GS_BASE = 0x10;

static const uint8_t IO_BASE = 0x40;

uint32_t gs_addr(uint32_t addr) {
    const uint32_t masked = addr & 0x00FFFFFF;

    return ((uint32_t)GS_BASE << 24) | (masked);
}

uint32_t read_gs(uint32_t addr) {
    const uint32_t pi_addr = gs_addr(addr);

    assertf(io_accessible(pi_addr), "PI address out of range\n");

    return io_read(pi_addr);
}

void write_gs(uint32_t addr, uint32_t data) {
    const uint32_t pi_addr = gs_addr(addr);

    assertf(io_accessible(pi_addr), "PI address out of range\n");

    return io_write(pi_addr, data);
}

uint32_t read_io(uint16_t addr) {
    const uint32_t gs_addr = ((uint32_t)IO_BASE << 16) | ((uint32_t)addr);

    return read_gs(gs_addr);
}

void write_io(uint16_t addr, uint16_t data_hi, uint16_t data_lo) {
    const uint32_t gs_addr = ((uint32_t)IO_BASE << 16) | ((uint32_t)addr);

    const uint32_t data = ((uint32_t)data_hi << 16) | ((uint32_t)data_lo);

    return write_gs(gs_addr, data);
}

int main(void) {
    data_cache_writeback_invalidate_all();
    inst_cache_invalidate_all();

    write_io(0x0400, 0x0000, 0x0000);

    display_init(RESOLUTION_640x240, DEPTH_16_BPP, 3, GAMMA_NONE, FILTERS_DISABLED);

    joypad_init();

    joypad_inputs_t inputs = { 0 }, prev_inputs;
    #define INPUT(inp) ((inputs.inp) && !(prev_inputs.inp))

    joypad_poll();
    inputs = joypad_get_inputs(JOYPAD_PORT_1);

    uint32_t addr = 0x10000000;

    bool run = false;

    uint16_t on = 0xFFFF;

    while (true) {
        if (run) {
            data_cache_writeback_invalidate_all();
            dma_read_async(rombuf, addr, 0x4000);
            surface_t * display = display_get();
            dma_wait();
            rombuf[0x4028] ^= 0x01;

            addr += 0x4000;
            if (addr > 0x14000000) {
                run = false;
                rombuf[0x4027] = 0x00;
                on = 0b0000011111000001;
            }

            uint16_t* ptr = display->buffer;
            uint16_t stride = display->stride / 2;

            for (int y = 0; y < 225; y++) {
                for (int x = 0; x < 584; x++) {
                    uint index = y * 584 + x;
                    uint pix_index = index / 8;
                    uint bit_index = index % 8;
                    ptr[y * stride + x + 8] = ((rombuf[pix_index] >> bit_index) & 1) ? on : 0x0000;
                }
            }

            display_show(display);
        }

        joypad_poll();
        prev_inputs = inputs;
        inputs = joypad_get_inputs(JOYPAD_PORT_1);

        if (INPUT(btn.a)) {
            addr = 0x10000000;
            run = true;
            rombuf[0x4027] = 0x01;
            on = 0xFFFF;
        }
    }
}
