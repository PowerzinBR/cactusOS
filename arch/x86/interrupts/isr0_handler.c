#include <cactus/terminal.h>

void isr0_handler_c(void) {
    terminal_writestring("[ISR0] Divide-by-zero or test interrupt triggered\n");
}
