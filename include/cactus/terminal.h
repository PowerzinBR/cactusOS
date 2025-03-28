#ifndef _CACTUS_TERMINAL_H
#define _CACTUS_TERMINAL_H

#include <stdint.h>
#include <stddef.h>
#include <asm/vga.h>

typedef enum {
    TERMINAL_LOG,
    TERMINAL_SUCCESS,
    TERMINAL_ERROR,
    TERMINAL_INFO
} terminal_message_type;

void terminal_write_message(terminal_message_type type, const char* message);
void terminal_get_cursor(size_t* x, size_t* y);
void terminal_set_cursor(size_t x, size_t y);
void terminal_writestring(const char* data);
void terminal_setcolor(uint8_t color);
void terminal_initialize(void);
void terminal_scroll(void);

#endif /* _CACTUS_TERMINAL_H */
