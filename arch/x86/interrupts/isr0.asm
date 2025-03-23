# Minimal ISR stub for interrupt 0
    .global isr0_stub
    .section .text

isr0_stub:
    pusha
    call isr0_handler_c
    popa

    iret
