## Global Descriptor Table design considerations.

- **GDT main directory**: [arch/x86/cpu/](../cpu/common.c)
- **GDT headers**: [arch/x86/include/desc.h](../include/asm/desc.h)

---

1. Flat Memory Model

    Base: 0x00000000 (start at zero)
    Limit: 0xFFFFF (4GB addressing with granularity bit set)
    This allows access to the full 32-bit address space without segmentation issues.

2. Code and Data Segments

    Kernel segments: Ring 0 (privileged)
    User segments: Ring 3 (restricted)
    Executable flag set for code segments.

3. TSS Support

    Required for switching stacks during privilege transitions (e.g., system calls, interrupts).