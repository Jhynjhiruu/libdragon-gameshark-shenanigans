BUILD_DIR := ../../build/bootstrap

TARGET := $(BUILD_DIR)/test.elf

default: $(TARGET)

$(shell mkdir -p ../../build/bootstrap)

$(BUILD_DIR)/test.elf: $(BUILD_DIR)/loader.o | bootstrap.ld loader.h debug.h minidragon.h
	mips64-elf-ld -o $@ -T bootstrap.ld $^

$(BUILD_DIR)/%.o: %.c
	mips64-elf-gcc -o $@ -c $< -march=vr4300 -mtune=vr4300 -mabi=o64 -falign-functions=32 -Wall -Wextra -I.

.PHONY: clean

clean:
	rm $(BUILD_DIR)/loader.o $(BUILD_DIR)/test.elf
