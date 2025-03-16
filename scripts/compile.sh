INIT_DIR="init"
KERNEL_DIR="kernel"
X86_DIR="arch/x86"
BUILD_DIR="build"

mkdir -p build

i686-elf-as ${X86_DIR}/boot/boot.s -o ${BUILD_DIR}/boot.o

i686-elf-gcc -c ${INIT_DIR}/main.c -o ${BUILD_DIR}/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -Iinclude
i686-elf-gcc -c ${KERNEL_DIR}/lib/string.c -o ${BUILD_DIR}/lib_string.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -Iinclude
i686-elf-gcc -c ${KERNEL_DIR}/terminal/terminal.c -o ${BUILD_DIR}/terminal_functions.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -Iinclude

i686-elf-gcc -T linker.ld -o ${BUILD_DIR}/os.bin -ffreestanding -O2 -nostdlib ${BUILD_DIR}/*.o -lgcc