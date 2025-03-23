#include <cactus/kernel.h>

#include "../include/asm/desc.h"
#include "../include/asm/idt_desc.h"

void kernel_boot() {
    gdt_init();
    idt_init();       // If needed, IDT can also be set up early
    kernel_main();    // Now enter the actual kernel
}
