#include <cactus/terminal.h>
#include <cactus/string.h>
#include <stdint.h>

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

void terminal_writedec(uint32_t num) {
    char buffer[11];  // Buffer to hold the decimal string (max 10 digits for uint32_t)
    int index = 0;

    if (num == 0) {
        buffer[index++] = '0';  // Handle the zero case
    } else {
        // Convert the number to a decimal string
        while (num > 0) {
            buffer[index++] = '0' + (num % 10);
            num /= 10;
        }
    }

    // Reverse the string and print it
    for (int i = index - 1; i >= 0; i--) {
        terminal_putchar(buffer[i]);
    }
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) {
    const size_t index = y * VGA_WIDTH + x;
    terminal_buffer[index] = vga_entry(c, color);
}

/* 
 * Scrolls the screen up by one line:
 *  1. Copy line y+1 to line y, for y in [0, VGA_HEIGHT-2].
 *  2. Clear the last line.
 *  3. Decrement terminal_row so that new text will appear at the bottom line.
 */
void terminal_scroll(void) {
    for (size_t y = 0; y < VGA_HEIGHT - 1; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            terminal_buffer[y * VGA_WIDTH + x] = terminal_buffer[(y + 1) * VGA_WIDTH + x];
        }
    }
    for (size_t x = 0; x < VGA_WIDTH; x++) {
        terminal_buffer[(VGA_HEIGHT - 1) * VGA_WIDTH + x] = vga_entry(' ', terminal_color);
    }
    if (terminal_row > 0) {
        terminal_row--;
    } else {
        terminal_row = VGA_HEIGHT - 1;
    }
}

void terminal_putchar(char c) {
    if (c == '\n') {
        terminal_column = 0;
        terminal_row++;
        if (terminal_row == VGA_HEIGHT) {
            terminal_scroll();
        }
    } else {
        terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
        terminal_column++;
        if (terminal_column == VGA_WIDTH) {
            terminal_column = 0;
            terminal_row++;
            if (terminal_row == VGA_HEIGHT) {
                terminal_scroll();
            }
        }
    }
}

void terminal_write(const char* data, size_t size) {
    for (size_t i = 0; i < size; i++) {
        terminal_putchar(data[i]);
    }
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
