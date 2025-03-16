#include <cactus/kernel.h>
#include <cactus/terminal.h>

void kernel_main() {
    terminal_initialize();
    
    terminal_write_message(TERMINAL_SUCCESS, "");
    terminal_writestring("Terminal initialized\n");

    terminal_write_message(TERMINAL_SUCCESS, "");

    terminal_setcolor(vga_entry_color(VGA_COLOR_YELLOW, VGA_COLOR_BLACK));
    terminal_writestring("Cactus version: ");
    
    terminal_setcolor(vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK));
    terminal_writestring("0.2.1\n\n");

    const char *grub_messages[] = {
        "Switched to protected mode",
        "Paging disabled"
    };

    for (int i = 0; i < 2; i++) {
        terminal_write_message(TERMINAL_SUCCESS, "");
        terminal_setcolor(vga_entry_color(VGA_COLOR_YELLOW, VGA_COLOR_BLACK));
        terminal_writestring("[BOOT]: ");
        
        terminal_setcolor(vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK));
        terminal_writestring(grub_messages[i]);
        terminal_writestring("\n");
    }

    terminal_setcolor(vga_entry_color(VGA_COLOR_LIGHT_BLUE, VGA_COLOR_BLACK));
    terminal_writestring("\n  Welcome to cactusOS!");
}
