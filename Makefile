# Directory variables
INIT_DIR = init
KERNEL_DIR = kernel
X86_DIR = arch/x86
BUILD_DIR = build
ISO_DIR = iso
BIN_FILE = os.bin

# Compiler and assembler
CC = i686-elf-gcc
AS = i686-elf-as
GRUB_MKRESCUE = grub-mkrescue
GRUB_FILE = grub-file
QEMU = qemu-system-i386

CFLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra -Iinclude -Iarch/x86/include
LDFLAGS = -T linker.ld -ffreestanding -O2 -nostdlib -lgcc

all: $(BUILD_DIR)/os.iso

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/boot.o: $(X86_DIR)/boot/boot.s | $(BUILD_DIR)
	$(AS) $< -o $@

$(BUILD_DIR)/kernel.o: $(INIT_DIR)/main.c | $(BUILD_DIR)
	$(CC) -c $< -o $@ $(CFLAGS)

$(BUILD_DIR)/lib_string.o: $(KERNEL_DIR)/lib/string.c | $(BUILD_DIR)
	$(CC) -c $< -o $@ $(CFLAGS)

$(BUILD_DIR)/terminal_functions.o: $(KERNEL_DIR)/terminal/terminal.c | $(BUILD_DIR)
	$(CC) -c $< -o $@ $(CFLAGS)

$(BUILD_DIR)/cpu_common.o: $(X86_DIR)/cpu/common.c | $(BUILD_DIR)
	$(CC) -c $< -o $@ $(CFLAGS)

$(BUILD_DIR)/lib_check_gdt.o: $(KERNEL_DIR)/lib/check_gdt.c | $(BUILD_DIR)
	$(CC) -c $< -o $@ $(CFLAGS)

$(BUILD_DIR)/desc.o: $(X86_DIR)/include/asm/desc.asm | $(BUILD_DIR)
	$(AS) $< -o $@

# -----------------------------------------
# Linker step
# -----------------------------------------
$(BUILD_DIR)/os.bin: $(BUILD_DIR)/boot.o $(BUILD_DIR)/kernel.o ${BUILD_DIR}/lib_check_gdt.o $(BUILD_DIR)/desc.o $(BUILD_DIR)/cpu_common.o $(BUILD_DIR)/lib_string.o $(BUILD_DIR)/terminal_functions.o | $(BUILD_DIR)
	$(CC) $(LDFLAGS) -o $@ $^

# -----------------------------------------
# Create ISO
# -----------------------------------------
$(BUILD_DIR)/os.iso: $(BUILD_DIR)/os.bin
	mkdir -p $(ISO_DIR)/boot
	cp $(BUILD_DIR)/os.bin $(ISO_DIR)/boot/
	$(GRUB_MKRESCUE) -o $@ $(ISO_DIR)

run: $(BUILD_DIR)/os.iso
	$(QEMU) -cdrom $(BUILD_DIR)/os.iso

# -----------------------------------------
multiboot:
	@if $(GRUB_FILE) --is-x86-multiboot $(BUILD_DIR)/os.bin; then \
		echo "multiboot CONFIRMED"; \
	else \
		echo "the file is NOT multiboot"; \
	fi

# -----------------------------------------
clean:
	rm -rf $(BUILD_DIR) $(ISO_DIR)/boot/os.bin

.PHONY: all clean run multiboot
