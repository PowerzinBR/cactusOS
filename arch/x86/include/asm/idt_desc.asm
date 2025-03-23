# ---------------------------------------
# Load Interrupt Descriptor Table (IDT)
# ---------------------------------------
# void load_idt(struct idt_ptr* idt_ptr);
#
# This function loads the IDT using the `lidt` instruction.
# The pointer to the IDT descriptor is passed as an argument
# in the stack (first argument at [esp + 4]).
#
# Parameters:
#   @esp+4: Pointer to struct idt_ptr (limit and base)
#
# Returns: None
# ---------------------------------------

    .global load_idt
    .type load_idt, @function
load_idt:
    movl 4(%esp), %eax   # Load IDT descriptor address from stack
    lidt (%eax)          # Load IDT into IDTR
    ret                  # Return to caller
