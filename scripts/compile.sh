INIT_DIR="init"
X86_DIR="arch/x86"
BUILD_DIR="build"

i686-elf-as ${X86_DIR}/boot/boot.s -o ${BUILD_DIR}/boot.o

i686-elf-gcc -c ${INIT_DIR}/main.c -o ${BUILD_DIR}/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

i686-elf-gcc -T linker.ld -o ${BUILD_DIR}/os.bin -ffreestanding -O2 -nostdlib ${BUILD_DIR}/boot.o ${BUILD_DIR}/kernel.o -lgcc