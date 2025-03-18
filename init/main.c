#include <cactus/kernel_modules_messages.h>
#include <cactus/grub_messages.h>
#include <cactus/terminal.h>
#include <cactus/version.h>
#include <cactus/process.h>
#include <cactus/kernel.h>
#include <cactus/string.h>
#include <cactus/host.h>

void kernel_main() {
    terminal_initialize();
    for (int i = 0; i < GRUB_MESSAGES_COUNT; i++) {
        terminal_setcolor(vga_entry_color(VGA_COLOR_DARK_GREY, VGA_COLOR_BLACK));
        terminal_writestring(HOST);

        terminal_setcolor(vga_entry_color(VGA_COLOR_LIGHT_BLUE, VGA_COLOR_BLACK));
        terminal_writestring(PROCESS);
        
        terminal_setcolor(vga_entry_color(VGA_COLOR_YELLOW, VGA_COLOR_BLACK));
        terminal_writestring(boot_messages[i]);
        terminal_writestring("\n");
    }

    for (int i = 0; i < MODULES_MESSAGE_COUNT; i++) {
        terminal_setcolor(vga_entry_color(VGA_COLOR_DARK_GREY, VGA_COLOR_BLACK));
        terminal_writestring(HOST);

        terminal_setcolor(vga_entry_color(VGA_COLOR_LIGHT_BLUE, VGA_COLOR_BLACK));
        terminal_writestring(PROCESS);
        
        terminal_setcolor(vga_entry_color(VGA_COLOR_YELLOW, VGA_COLOR_BLACK));
        terminal_writestring(modules_messages[i]);
        terminal_writestring("\n");
    }


    terminal_setcolor(vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK));
    terminal_writestring("\nKernel version: ");
    terminal_writestring(KERNEL_VERSION);
    terminal_writestring("\n");
}
