#include <cactus/terminal.h>
#include <cactus/string.h>

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

void terminal_initialize(void) {
    terminal_row = 0;
    terminal_column = 0;
    terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    terminal_buffer = (uint16_t*) 0xB8000;
    
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = vga_entry(' ', terminal_color);
        }
    }
}

void terminal_setcolor(uint8_t color) {
    terminal_color = color;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) {
    const size_t index = y * VGA_WIDTH + x;
    terminal_buffer[index] = vga_entry(c, color);
}

void terminal_putchar(char c) {
    if (c == '\n') {
        terminal_column = 0;
        if (++terminal_row == VGA_HEIGHT) {
            terminal_row = 0;
        }
    } else {
        terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
        if (++terminal_column == VGA_WIDTH) {
            terminal_column = 0;
            if (++terminal_row == VGA_HEIGHT) {
                terminal_row = 0;
            }
        }
    }
}

void terminal_write(const char* data, size_t size) {
    for (size_t i = 0; i < size; i++)
        terminal_putchar(data[i]);
}

void terminal_writestring(const char* data) {
    terminal_write(data, strlen(data));
}

void terminal_write_message(terminal_message_type type, const char* message) {
    uint8_t fg_color, bg_color;

    // Set colors based on message type
    switch (type) {
        case TERMINAL_LOG:
            fg_color = VGA_COLOR_LIGHT_GREY;
            bg_color = VGA_COLOR_BLACK;
            break;
        case TERMINAL_SUCCESS:
            fg_color = VGA_COLOR_GREEN;
            bg_color = VGA_COLOR_BLACK;
            break;
        case TERMINAL_ERROR:
            fg_color = VGA_COLOR_RED;
            bg_color = VGA_COLOR_BLACK;
            break;
        case TERMINAL_INFO:
            fg_color = VGA_COLOR_CYAN;
            bg_color = VGA_COLOR_BLACK;
            break;
        default:
            fg_color = VGA_COLOR_LIGHT_GREY;
            bg_color = VGA_COLOR_BLACK;
            break;
    }

    terminal_setcolor(vga_entry_color(fg_color, bg_color));
    terminal_writestring(message);
    terminal_writestring("\n");
}
