#include <cactus/bmessages.h>
#include <cactus/terminal.h>
#include <cactus/version.h>
#include <cactus/process.h>
#include <cactus/kernel.h>
#include <cactus/host.h>

void kernel_main() {
    terminal_initialize();

    for (int i = 0; i < BOOT_MESSAGES_COUNT; i++) {
        terminal_setcolor(vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK));

        terminal_writestring(HOST);
        terminal_writestring(" ");
        terminal_writestring(PROCESS);
        terminal_writestring(" ");
        
        terminal_setcolor(vga_entry_color(VGA_COLOR_YELLOW, VGA_COLOR_BLACK));
        terminal_writestring(boot_messages[i]);
        terminal_writestring("\n");
    }

    terminal_writestring("\n");

    terminal_setcolor(vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK));
    terminal_writestring("Terminal initialized\n");

    terminal_setcolor(vga_entry_color(VGA_COLOR_BROWN, VGA_COLOR_BLACK));
    terminal_writestring("Kernel version: ");
    terminal_writestring(KERNEL_VERSION);
    terminal_writestring("\n");
}
