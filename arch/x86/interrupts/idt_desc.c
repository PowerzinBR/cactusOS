/*
    * idt_desc.c:: Interrupt Descriptor Table (IDT) Initialization and Debugging
    *
    * This file contains the implementation for setting up the IDT, installing ISRs,
    * and debugging the IDT state. It also provides a simple printf function to aid debugging.
    *
*/

#include <cactus/terminal.h>
#include <cactus/kernel.h>
#include <stdint.h>
#include <stdarg.h>

#include "../include/asm/idt_desc.h"

/*
* Helper function to print a hexadecimal number with a specific width.
*
* @param num: The number to print in hexadecimal.
* @param width: The minimum width of the output (e.g., %04x ensures at least 4 hex digits).
*/
static void idt_terminal_writehex(uint32_t num, int width) {
    char hex[9];
    hex[8] = '\0';
    for (int i = 7; i >= 0; i--) {
        uint32_t nibble = num & 0xF;
        hex[i] = (nibble < 10) ? '0' + nibble : 'A' + (nibble - 10);
        num >>= 4;
    }
    
    // Only print the requested width (assuming width <= 8)
    terminal_writestring("0x");
    terminal_writestring(&hex[8 - width]);
}

/*
* Simple formatted print function supporting %d (decimal), %s (string), and %x (hexadecimal).
*
* @param format: The format string.
* @param ...: Variable arguments based on format specifiers.
*/
void printf(const char* format, ...) {
    va_list args;
    va_start(args, format);
    
    while (*format) {
        if (*format == '%') {
            format++; // Skip '%'
            
            int width = 0;
            while (*format >= '0' && *format <= '9') {
                width = width * 10 + (*format - '0');
                format++;
            }
            if (width == 0) {
                width = 8;
            }
            
            if (*format == 'd') {
                int32_t num = va_arg(args, int32_t);
                terminal_writedec(num);
            }
            else if (*format == 's') {
                const char* str = va_arg(args, const char*);
                terminal_writestring(str);
            }
            else if (*format == 'x') {
                uint32_t num = va_arg(args, uint32_t);
                idt_terminal_writehex(num, width);
            }
        } else {
            terminal_putchar(*format);
        }
        format++;
    }
    
    va_end(args);
}

/* Declare the IDT array and the IDT descriptor */
struct idt_entry idt[IDT_ENTRY_COUNT];
struct idt_ptr idt_descriptor;

extern void isr0_stub(void);

/*
* Installs ISR0 (Divide-by-Zero) into the IDT.
*
* This function sets up the first entry in the IDT (vector 0) to handle
* divide-by-zero exceptions.
*/
void idt_install_isr0(void) {
    idt_set_entry(0, (uint32_t)isr0_stub, 0x08, 0x8E);
    /*
    - index 0 = interrupt vector 0 (divide-by-zero)
    - base = address of isr0_stub
    - selector = 0x08 (kernel code segment in GDT)
    - flags = 0x8E (present, ring 0, 32-bit interrupt gate)
    */
}

void idt_set_entry(int index, uint32_t base, uint16_t selector, uint8_t flags) {
    idt[index].offset_low = base & 0xFFFF;
    idt[index].selector = selector;
    idt[index].zero = 0;
    idt[index].type_attr = flags;
    idt[index].offset_middle = (base >> 16) & 0xFFFF;
    idt[index].offset_high = (base >> 32) & 0xFFFFFFFF;
    idt[index].reserved = 0;
}

/*
* Initializes the IDT by clearing all entries and setting up the descriptor.
*
* This function prepares the IDT by zeroing all entries and configuring the
* IDT descriptor. Individual ISRs should be installed before loading the IDT.
*/
void idt_init(void) {
    // Initialize the IDT with zeroes
    for (int i = 0; i < IDT_ENTRY_COUNT; i++) {
        idt[i].offset_low = 0;
        idt[i].offset_middle = 0;
        idt[i].offset_high = 0;
        idt[i].selector = 0;
        idt[i].zero = 0;
        idt[i].type_attr = 0;
    }

    // Set up the IDT descriptor
    idt_descriptor.limit = sizeof(idt) - 1;
    idt_descriptor.base = (uint32_t)&idt;

    // Load the IDT (assumes load_idt function exists)
    load_idt(&idt_descriptor);
}

/*
* Debugging function to print the first 10 entries of the IDT.
*
* This function prints the IDT entries in the format:
*    IDT[index]: 0x[offset] (selector=0x[selector], type_attr=0x[type])
*/
void debug_print_idt(void) {
    // Todo: Replace 5 with IDT entry count
    for (int i = 0; i < 5; i++) {
        uint32_t offset = (idt[i].offset_high << 16) | (idt[i].offset_middle << 8) | idt[i].offset_low;
        terminal_setcolor(vga_entry_color(VGA_COLOR_GREEN, VGA_COLOR_BLACK));
        terminal_writestring(HOST);

        terminal_setcolor(vga_entry_color(VGA_COLOR_YELLOW, VGA_COLOR_BLACK));
        terminal_writestring(PROCESS);

        terminal_setcolor(vga_entry_color(VGA_COLOR_LIGHT_BLUE, VGA_COLOR_BLACK));
        printf("IDT[%d]: ", i);

        terminal_setcolor(vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK));
        printf("0x%08x ", offset); 

        terminal_setcolor(vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK));
        printf("(selector=0x%04x, type_attr=0x%02x)", idt[i].selector, idt[i].type_attr);
    }
}
