/*
* ------------------------------------
* Global Descriptor Table initialization and management.
* ------------------------------------
*/

#include <stdint.h>

#include "../include/asm/desc.h"

/* GDT table */
struct gdt_entry gdt[6];
struct gdt_ptr gdt_descriptor;

/* TSS */
struct tss_entry tss;

/* Helper fn to set a GDT entry */
static void set_gdt_entry(int index, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity) {
  gdt[index].base_low = base & 0xFFFF;
  gdt[index].base_middle = (base >> 16) & 0xFF;
  gdt[index].base_high = (base >> 24) & 0xFF;

  gdt[index].limit_low = limit & 0xFFFF;
  gdt[index].granularity = (limit >> 16) & 0x0F;
  
  gdt[index].granularity |= granularity & 0xF0;
  gdt[index].access = access;
}

static void tss_init(uint32_t kernel_stack) {
  /* Clear TSS and set ring 0 stack */
  
  for (int i = 0; i < sizeof(tss); i++) ((char*)&tss)[i] = 0;
  tss.esp0 = kernel_stack;
  tss.ss0 = 0x10;               /* Kernel Data Segment */
  tss.iomap_base = sizeof(tss); /* Disable I/O map */

  /* Set GDT entry for TSS */
  set_gdt_entry(5, (uint32_t)&tss, sizeof(tss) - 1, 0x89, 0x40);
}

/* GDT initialization */
void gdt_init(void) {
  gdt_descriptor.limit = sizeof(gdt) - 1;
  gdt_descriptor.base = (uint32_t)&gdt;

  /* Null segment */
  set_gdt_entry(0, 0, 0, 0, 0);

  /* Kernel Code Segment */
  set_gdt_entry(1, 0, 0xFFFFF, 0x9A, 0xCF);

  /* Kernel Data Segment */
  set_gdt_entry(2, 0, 0xFFFFF, 0x92, 0xCF);

  /* User Code Segment */
  set_gdt_entry(3, 0, 0xFFFFF, 0xFA, 0xCF);

  /* User Data Segment */
  set_gdt_entry(4, 0, 0xFFFFF, 0xF2, 0xCF);

  /* Initialize TSS */
  tss_init(0x0); /* Set actual stack address later */

  /* Load GDT */
  load_gdt(&gdt_descriptor);

  /* Load TSS */
  load_tss(5 * 8);
}
