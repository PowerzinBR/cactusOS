ENTRY(_start)

/* A memória do kernel é carregada a partir de 2MB */
SECTIONS
{
    . = 2M; /* Posição inicial do kernel */
    
    /* Colocando o header Multiboot no início da memória */
    .multiboot : { *(.multiboot) }

    /* Código do kernel */
    .text : {
        *(.text)
    }

    /* Dados somente leitura */
    .rodata : {
        *(.rodata)
    }

    /* Dados de leitura e escrita (inicializados) */
    .data : {
        *(.data)
    }

    /* Dados de leitura e escrita (não inicializados) */
    .bss : {
        *(.bss)
    }

    /* Marca o final do kernel */
    _kernel_end = .;

    /* Definição do topo do heap */
    _heap_start = .;

    /* Alocando a pilha */
    .stack : {
        *(.stack)
    }
}
