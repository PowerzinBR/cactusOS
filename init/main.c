#include <cactus/kernel_modules_messages.h>
#include <cactus/grub_messages.h>
#include <cactus/check_gdt.h>
#include <cactus/terminal.h>
#include <cactus/version.h>
#include <cactus/process.h>
#include <cactus/kernel.h>
#include <cactus/string.h>
#include <cactus/host.h>
#include <stdbool.h>

#include "../arch/x86/include/asm/desc.h"

void kernel_main() {
    gdt_init();
    terminal_initialize();

    for (int i = 0; i < GRUB_MESSAGES_COUNT; i++) {
        terminal_setcolor(vga_entry_color(VGA_COLOR_GREEN, VGA_COLOR_BLACK));
        terminal_writestring(HOST);

        terminal_setcolor(vga_entry_color(VGA_COLOR_YELLOW, VGA_COLOR_BLACK));
        terminal_writestring(PROCESS);
        
        terminal_setcolor(vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK));
        terminal_writestring(boot_messages[i]);
        terminal_writestring("\n");
    }

    for (int i = 0; i < MODULES_MESSAGE_COUNT; i++) {
        terminal_setcolor(vga_entry_color(VGA_COLOR_GREEN, VGA_COLOR_BLACK));
        terminal_writestring(HOST);

        terminal_setcolor(vga_entry_color(VGA_COLOR_YELLOW, VGA_COLOR_BLACK));
        terminal_writestring(PROCESS);
        
        terminal_setcolor(vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK));
        terminal_writestring(modules_messages[i]);
        terminal_writestring("\n");
    }

    terminal_setcolor(vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK));
    terminal_writestring("                      Kernel version: ");
    terminal_writestring(KERNEL_VERSION);
    terminal_writestring("\n");

    check_gdt_minimized();
}
