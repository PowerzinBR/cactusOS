BUILD_DIR="build/"
BIN_FILE="os.bin"

cp -r ${BUILD_DIR}/${BIN_FILE} iso/boot/
grub-mkrescue -o ${BUILD_DIR}/os.iso iso/