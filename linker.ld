/* Define the memory region for the kernel.
   The kernel will load at 0x200000 and has 2 MB of space. */
MEMORY
{
    KERNEL (rwx) : ORIGIN = 0x200000, LENGTH = 2M
}

/* Entry point of the kernel */
ENTRY(_start)

SECTIONS
{
    /* 
       Force the file to start at offset 0. This ensures that the .multiboot 
       section is placed at the very beginning of the file, within the first 8 KB.
    */
    . = 0x0;

    /* 
       Place the Multiboot header at the very beginning of the file.
       KEEP() prevents the linker from discarding it, even if it's not referenced.
    */
    .multiboot : {
        KEEP(*(.multiboot))
    } > KERNEL

    /*
       Move the location counter to the kernel load address.
       Subsequent sections will be loaded at 0x200000.
    */
    . = 0x200000;

    /* Kernel code */
    .text : {
        *(.text)
    } > KERNEL

    /* Read-only data */
    .rodata : {
        *(.rodata)
    } > KERNEL

    /* Initialized data */
    .data : {
        *(.data)
    } > KERNEL

    /* Uninitialized data (BSS) */
    .bss : {
        *(.bss)
        *(COMMON)
    } > KERNEL

    /* Mark the end of the kernel */
    _kernel_end = .;

    /* Define the start of the heap (if needed) */
    _heap_start = .;

    /* Reserve space for the kernel stack */
    .stack : {
        . = ALIGN(16);
        KEEP(*(.stack))
        /* Reserve 64 KB for the stack */
        . += 0x10000;
        . = ALIGN(16);
    } > KERNEL
}
