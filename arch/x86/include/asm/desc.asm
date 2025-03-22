# ---------------------------------------
# Load Global Descriptor Table (GDT)
# ---------------------------------------
# void load_gdt(struct gdt_ptr* gdt_ptr);
#
# This function loads the GDT using the `lgdt` instruction.
# The pointer to the GDT descriptor is passed as an argument
# in the stack (first argument at [esp + 4]).
#
# Parameters:
#   @esp+4: Pointer to struct gdt_ptr (limit and base)
#
# Returns: None
# ---------------------------------------

    .global load_gdt
    .type load_gdt, @function
load_gdt:
    movl 4(%esp), %eax   # Load GDT descriptor address from stack
    lgdt (%eax)          # Load GDT into GDTR
    ret                  # Return to caller

# ---------------------------------------
# Load Task State Segment (TSS)
# ---------------------------------------
# void load_tss(uint16_t tss_selector);
#
# This function loads the Task Register (TR) with the given TSS selector.
# The selector must reference a valid TSS entry in the GDT.
#
# Parameters:
#   @esp+4: TSS segment selector (uint16_t)
#
# Returns: None
# ---------------------------------------

    .global load_tss
    .type load_tss, @function
load_tss:
    movw 4(%esp), %ax   # Load TSS selector from stack
    ltr  %ax            # Load Task Register (TR) with selector
    ret                 # Return to caller
