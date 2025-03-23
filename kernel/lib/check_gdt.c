#include <cactus/terminal.h>
#include <cactus/kernel.h>
#include <stdint.h>

#include "../../arch/x86/include/asm/desc.h"

/* Simple error logging buffer */
#define MAX_ERROR_LOG_SIZE 256
static char error_log[MAX_ERROR_LOG_SIZE];
static uint32_t error_log_index = 0;

/* Append an error message to our log */
static void log_error(const char *msg) {
    for (uint32_t i = 0; msg[i] != '\0'; i++) {
        if (error_log_index < MAX_ERROR_LOG_SIZE - 1) {
            error_log[error_log_index++] = msg[i];
        }
    }
    if (error_log_index < MAX_ERROR_LOG_SIZE - 1) {
        error_log[error_log_index++] = '\n';
    }
}

/* Print the error log to the terminal */
static void print_error_log(void) {
    terminal_writestring("Error Log:\n");
    terminal_writestring(error_log);
}

/* Convert a 32-bit integer to a hexadecimal string.
 * The output buffer must be at least 11 characters long.
 */
static void int_to_hex(uint32_t num, char *buffer) {
    const char *hex_chars = "0123456789ABCDEF";
    buffer[0] = '0';
    buffer[1] = 'x';
    for (int i = 0; i < 8; i++) {
        buffer[2 + i] = hex_chars[(num >> (28 - 4 * i)) & 0xF];
    }
    buffer[10] = '\0';
}

/* Convert an unsigned integer to a decimal string.
 * This simple version writes into buffer, which should be at least 11 characters.
 */
static void int_to_dec(uint32_t num, char *buffer) {
    char temp[11];
    int index = 0;
    if (num == 0) {
        buffer[0] = '0';
        buffer[1] = '\0';
        return;
    }
    while (num > 0 && index < 10) {
        temp[index++] = '0' + (num % 10);
        num /= 10;
    }
    // Reverse the digits into buffer
    for (int i = 0; i < index; i++) {
        buffer[i] = temp[index - i - 1];
    }
    buffer[index] = '\0';
}

void check_gdt_minimized(void) {
    struct gdt_ptr current_gdt;
    char hex_buffer[11];
    char dec_buffer[11];

    /* Read the current GDTR into current_gdt */
    asm volatile("sgdt %0" : "=m"(current_gdt));

    /* Print current GDTR values */
    terminal_setcolor(vga_entry_color(VGA_COLOR_GREEN, VGA_COLOR_BLACK));
    terminal_writestring(HOST);

    terminal_setcolor(vga_entry_color(VGA_COLOR_YELLOW, VGA_COLOR_BLACK));
    terminal_writestring(PROCESS);

    terminal_setcolor(vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK));
    int_to_hex(current_gdt.base, hex_buffer);
    terminal_writestring("Current GDTR Base: ");
    terminal_writestring(hex_buffer);
    terminal_writestring("\n");

    terminal_setcolor(vga_entry_color(VGA_COLOR_GREEN, VGA_COLOR_BLACK));
    terminal_writestring(HOST);

    terminal_setcolor(vga_entry_color(VGA_COLOR_YELLOW, VGA_COLOR_BLACK));
    terminal_writestring(PROCESS);

    terminal_setcolor(vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK));
    int_to_hex(current_gdt.limit, hex_buffer);
    terminal_writestring("Current GDTR Limit: ");
    terminal_writestring(hex_buffer);
    terminal_writestring("\n");

    terminal_setcolor(vga_entry_color(VGA_COLOR_GREEN, VGA_COLOR_BLACK));
    terminal_writestring(HOST);

    terminal_setcolor(vga_entry_color(VGA_COLOR_YELLOW, VGA_COLOR_BLACK));
    terminal_writestring(PROCESS);

    /* Print expected GDTR values */
    terminal_setcolor(vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK));
    int_to_hex(gdt_descriptor.base, hex_buffer);
    terminal_writestring("Expected GDTR Base: ");
    terminal_writestring(hex_buffer);
    terminal_writestring("\n");

    terminal_setcolor(vga_entry_color(VGA_COLOR_GREEN, VGA_COLOR_BLACK));
    terminal_writestring(HOST);

    terminal_setcolor(vga_entry_color(VGA_COLOR_YELLOW, VGA_COLOR_BLACK));
    terminal_writestring(PROCESS);

    terminal_setcolor(vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK));
    int_to_hex(gdt_descriptor.limit, hex_buffer);
    terminal_writestring("Expected GDTR Limit: ");
    terminal_writestring(hex_buffer);
    terminal_writestring("\n");

    if (current_gdt.base != gdt_descriptor.base || current_gdt.limit != gdt_descriptor.limit) {
        terminal_setcolor(vga_entry_color(VGA_COLOR_GREEN, VGA_COLOR_BLACK));
        terminal_writestring(HOST);
    
        terminal_setcolor(vga_entry_color(VGA_COLOR_LIGHT_RED, VGA_COLOR_BLACK));
        terminal_writestring("ERROR");
    
        terminal_setcolor(vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK));
        terminal_writestring("GDT Check Failed: GDTR mismatch.\n");
        log_error("GDTR mismatch between loaded GDT and expected descriptor.");
    } else {
        terminal_setcolor(vga_entry_color(VGA_COLOR_GREEN, VGA_COLOR_BLACK));
        terminal_writestring(HOST);
    
        terminal_setcolor(vga_entry_color(VGA_COLOR_YELLOW, VGA_COLOR_BLACK));
        terminal_writestring(PROCESS);
    
        terminal_setcolor(vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK));
        terminal_writestring("GDT Loaded Successfully.\n");
    }

    /* Calculate the number of GDT entries:
     * Each GDT entry is sizeof(struct gdt_entry) bytes.
     */
    uint32_t num_entries = (gdt_descriptor.limit + 1) / sizeof(struct gdt_entry);
    int_to_dec(num_entries, dec_buffer);
    
    terminal_setcolor(vga_entry_color(VGA_COLOR_GREEN, VGA_COLOR_BLACK));
    terminal_writestring(HOST);

    terminal_setcolor(vga_entry_color(VGA_COLOR_YELLOW, VGA_COLOR_BLACK));
    terminal_writestring(PROCESS);

    terminal_setcolor(vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK));

    terminal_writestring("Number of GDT entries: ");
    terminal_writestring(dec_buffer);
    terminal_writestring("\n");

    /* Print the error log if there were any errors */
    if (error_log_index > 0) {
        print_error_log();
    }
}
