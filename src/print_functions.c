#include "print_functions.h"

#include <stdio.h>
#include "../include/memory.h"


void printMemory(Neander cpu) {
    printf("\nInstrucoes na memoria:\n");
    for (int i = 0; i < 512; i++) {
        if (i + 2 < 512) { // Guarda de acesso
            switch (cpu.memoria[i]) {
                case  16:
                    printf("STA %03d\n", cpu.memoria[i+2]);
                    i += 2;
                    break;
                case  32:
                    printf("LDA %03d\n", cpu.memoria[i+2]);
                    i += 2;
                    break;
                case  48:
                    printf("ADD %03d\n", cpu.memoria[i+2]);
                    i += 2;
                    break;
                case  64:
                    printf("OR %03d\n", cpu.memoria[i+2]);
                    i += 2;
                    break;
                case  80:
                    printf("AND %03d\n", cpu.memoria[i+2]);
                    i += 2;
                    break;
                case  96:
                    printf("NOT\n");
                    break;
                case  128:
                    printf("JMP %03d\n", cpu.memoria[i+2]);
                    i += 2;
                    break;
                case  144:
                    printf("JN  %03d\n", cpu.memoria[i+2]);
                    i += 2;
                    break;
                case  160:
                    printf("JZ  %03d\n", cpu.memoria[i+2]);
                    i += 2;
                    break;
                case  240:
                    printf("HLT\n");
                    break;
            }
        }
    }
}

void printMemoryVARS(Neander cpu) {
    for (int i = 256; i < 512; i++)
        printf("%03d: %02d  ", i, cpu.memoria[i]);
    printf("\n");
}

void printMemoryASIS(Neander cpu) {
    for (int i = 0; i < 512; i++) {
        printf("%02d ", cpu.memoria[i]);
    }
}

void printStates(Neander cpu) {
    printf("AC: %03d PC: %03d\n", cpu.acumulador, cpu.pc/2);
    printf("N:  %03d Z:  %03d\n", cpu.negativo, cpu.zero);
}