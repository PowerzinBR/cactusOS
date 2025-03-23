#ifndef IDT_DESC_H
#define IDT_DESC_H

#include <stdint.h>

/* Structure that represents an entry in the IDT */
struct idt_entry {
    uint16_t offset_low;    // Lower 16 bits of the address
    uint16_t selector;      // Code segment selector
    uint8_t zero;           // Reserved, should be 0
    uint8_t type_attr;      // Type and attributes (e.g., gate type, privilege level)
    uint16_t offset_middle; // Middle 16 bits of the address
    uint32_t offset_high : 32;  // Upper 32 bits of the address
    uint32_t reserved : 32; // Reserved (set to 0)
} __attribute__((packed));


/* Structure for IDT descriptor */
struct idt_ptr {
    uint16_t limit;          // Size of the IDT - 1
    uint32_t base;           // Base address of the IDT
} __attribute__((packed));

#define IDT_ENTRY_COUNT 256

extern struct idt_entry idt[256]; 

extern void load_idt(struct idt_ptr* idt_descriptor);
void idt_set_entry(int index, uint32_t base, uint16_t selector, uint8_t flags);

void debug_print_idt(void);
void idt_init(void);

#endif // IDT_DESC_H
