if grub-file --is-x86-multiboot build/os.bin; then
  echo multiboot CONFIRMED
else
  echo the file is NOT multiboot
fi
