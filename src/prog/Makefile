all: prog.z64
.PHONY: all

BUILD_DIR = ../../build/prog
SOURCE_DIR = ./
include $(N64_INST)/include/n64.mk

OBJS = $(BUILD_DIR)/main.o

N64_CFLAGS += -Ofast -G0

$(BUILD_DIR)/prog.elf: $(OBJS)

clean:
	rm -rf $(BUILD_DIR)
.PHONY: clean

-include $(wildcard $(BUILD_DIR)/*.d)
