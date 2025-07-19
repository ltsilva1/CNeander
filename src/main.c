#include <stdio.h>

#include "../include/memory.h"
#include "../include/print_functions.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s <arquivo_entrada.mem>\n", argv[0]);
        printf("Exemplo: %s entrada.mem\n", argv[0]);
        return 1;
    }

    Neander cpu;
    clearMemory(&cpu);

    loadMemory(&cpu, argv[1]);
    printMemory(cpu);

    executeMemory(&cpu);
    printStates(cpu);

    exportMemory(&cpu, "out.mem");

    return 0;
}
