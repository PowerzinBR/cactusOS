#include <cactus/kernel.h>
#include <cactus/terminal.h>

void kernel_main(const char *cmdline) {
    terminal_initialize();

    const char *host = "Default-Host";
    const char *process = "kernel[0]";

    const char *boot_messages[] = {
        "GRUB loaded",
        "Reading GRUB configuration",
        "Switching to protected mode",
        "Enabling 32-bit mode",
        "Disabling paging",
        "Loading kernel modules",
        "Kernel initialization complete"
    };

    for (int i = 0; i < sizeof(boot_messages) / sizeof(boot_messages[0]); i++) {
        terminal_setcolor(vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK));
        terminal_writestring(host);
        terminal_writestring(" ");
        terminal_writestring(process);
        terminal_writestring(": ");

        terminal_setcolor(vga_entry_color(VGA_COLOR_YELLOW, VGA_COLOR_BLACK));
        terminal_writestring("Boot: ");

        terminal_setcolor(vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK));
        terminal_writestring(boot_messages[i]);
        terminal_writestring("\n");
    }

    terminal_writestring("\n");

    terminal_setcolor(vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK));
    terminal_writestring(host);
    terminal_writestring(" ");
    terminal_writestring(process);
    terminal_writestring(": ");

    terminal_setcolor(vga_entry_color(VGA_COLOR_YELLOW, VGA_COLOR_BLACK));

    terminal_setcolor(vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK));
    terminal_writestring("Terminal initialized\n");

    terminal_setcolor(vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK));
    terminal_writestring(host);
    terminal_writestring(" ");
    terminal_writestring(process);
    terminal_writestring(": ");

    terminal_setcolor(vga_entry_color(VGA_COLOR_YELLOW, VGA_COLOR_BLACK));

    terminal_setcolor(vga_entry_color(VGA_COLOR_BROWN, VGA_COLOR_BLACK));
    terminal_writestring("Kernel version: ");

    terminal_setcolor(vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK));
    terminal_writestring("0.2.3\n\n");
}
