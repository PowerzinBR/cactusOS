/*
* ------------------------------------
* Global Descriptor Table (GDT) structures and loading functions.
* ------------------------------------
*/

#ifndef _ASM_DESC_H
#define _ASM_DESC_H

#include <stdint.h>

/* GDT entry structure */
struct gdt_entry {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_high;
} __attribute__((packed));

/* GDT pointer structure */
struct gdt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

/* Task State Segment (TSS) structure */
struct tss_entry {
    uint32_t prev_tss;
    uint32_t esp0;  /* Stack pointer for ring 0 */
    uint32_t ss0;   /* Stack segment for ring 0 */
    uint32_t esp1;
    uint32_t ss1;
    uint32_t esp2;
    uint32_t ss2;
    uint32_t cr3;
    uint32_t eip;
    uint32_t eflags;
    uint32_t eax, ecx, edx, ebx;
    uint32_t esp, ebp, esi, edi;
    uint32_t es, cs, ss, ds, fs, gs;
    uint32_t ldt;
    uint16_t trap;
    uint16_t iomap_base;
} __attribute__((packed));

/* GDT table and TSS */
extern struct gdt_entry gdt[];
extern struct gdt_ptr gdt_descriptor;
extern struct tss_entry tss;

/* Functions to load GDT and TSS */
void load_gdt(struct gdt_ptr* gdt_ptr);
void load_tss(uint16_t tss_selector);

/* GDT initialization */
void gdt_init(void);

#endif /* _ASM_DESC_H */ 