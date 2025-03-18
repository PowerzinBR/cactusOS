
# cactusOS

This is a basic operating system created using the **Bare Bones guide** from [OSDev](https://osdev.org).

## Table of Contents
- [Compiling cactusOS](#compiling-cactusos)
- [Requirements](#requirements)
- [Running cactusOS](#running-cactusos)
- [TODO](#todo)

---

## Compiling cactusOS

### Requirements
To build cactusOS, you need the following tools installed:  
- `i686-elf-binutils`
- `i686-elf-gcc` / `i686-elf-g++`
- `grub-mkrescue`
- `qemu-system-i386`

### Build Process
To compile the OS, run:  
```sh
make
```

This will generate an ISO image in the `build/` directory.

---

## Running cactusOS

### Using QEMU
To boot cactusOS in QEMU, run:  
```sh
make run
```

### Checking Multiboot Compatibility
To verify that `cactusOS` is a Multiboot-compatible kernel, use:  
```sh
make multiboot
```

---

## TODO
- Improve this README.md
- Implement more kernel features
- Read /etc/hostname when implementing a filesystem
- Implement a fat filesystem
- Implement interrupts