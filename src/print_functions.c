#include "print_functions.h"

#include <stdio.h>
#include "../include/memory.h"


void printMemory(Neander cpu) {
    printf("\nInstrucoes na memoria:\n");
    int i = 0;
    while (i < 128) {
        uint8_t opcode = cpu.memoria[i];
        if (i + 1 < 128) { // Guarda de acesso
            switch (opcode) {
                case  16:
                    printf("STA %03d\n", cpu.memoria[i+1]);
                    i += 2;
                    break;
                case  32:
                    printf("LDA %03d\n", cpu.memoria[i+1]);
                    i += 2;
                    break;
                case  48:
                    printf("ADD %03d\n", cpu.memoria[i+1]);
                    i += 2;
                    break;
                case  64:
                    printf("OR %03d\n", cpu.memoria[i+1]);
                    i += 2;
                    break;
                case  80:
                    printf("AND %03d\n", cpu.memoria[i+1]);
                    i += 2;
                    break;
                case  96:
                    printf("NOT\n");
                    i += 1;
                    break;
                case  128:
                    printf("JMP %03d\n", cpu.memoria[i+1]);
                    i += 2;
                    break;
                case  144:
                    printf("JN  %03d\n", cpu.memoria[i+1]);
                    i += 2;
                    break;
                case  160:
                    printf("JZ  %03d\n", cpu.memoria[i+1]);
                    i += 2;
                    break;
                case  240:
                    printf("HLT\n");
                    i += 1;
                    return;
                default:
                    printf("NOP\n");
                    i += 1;
                    break;
            }
        } else {
            if (opcode == 96) printf("NOT\n");
            else if (opcode == 240) printf("HLT\n");
            else printf("NOP\n");
            i += 1;
        }
    }
}

void printMemoryVARS(Neander cpu, FILE *arq) {
    fprintf(arq,"Variaveis:\n");
    for (int i = 128; i < 256; i++)
        fprintf(arq,"%03d: %02d\n", i, cpu.memoria[i]);
}

void printMemoryASIS(Neander cpu) {
    for (int i = 0; i < 256; i++) {
        printf("%02d ", cpu.memoria[i]);
    }
}

void printStates(Neander cpu) {
    printf("AC: %03d PC: %03d\n", cpu.acumulador, cpu.pc);
    printf("N:  %03d Z:  %03d\n", cpu.negativo, cpu.zero);
}

void printToTxt(Neander cpu, const char nomeArquivo[]) {
    char nomeArquivoTXT[100];
    sprintf(nomeArquivoTXT, "%s.txt", nomeArquivo);

    FILE* arquivoTXT = fopen(nomeArquivoTXT, "w");
    int i = 0;
    while (i < 128) {
        uint8_t opcode = cpu.memoria[i];
        if (i + 1 < 128) { // Guarda de acesso
            switch (opcode) {
                case  16:
                    fprintf(arquivoTXT, "%03d: STA %03d\n", i, cpu.memoria[i+1]);
                    i += 2;
                    break;
                case  32:
                    fprintf(arquivoTXT, "%03d: LDA %03d\n", i, cpu.memoria[i+1]);
                    i += 2;
                    break;
                case  48:
                    fprintf(arquivoTXT, "%03d: ADD %03d\n", i, cpu.memoria[i+1]);
                    i += 2;
                    break;
                case  64:
                    fprintf(arquivoTXT, "%03d: OR %03d\n", i, cpu.memoria[i+1]);
                    i += 2;
                    break;
                case  80:
                    fprintf(arquivoTXT, "%03d: AND %03d\n", i, cpu.memoria[i+1]);
                    i += 2;
                    break;
                case  96:
                    fprintf(arquivoTXT, "%03d: NOT\n", i);
                    i += 1;
                    break;
                case  128:
                    fprintf(arquivoTXT, "%03d: JMP %03d\n", i, cpu.memoria[i+1]);
                    i += 2;
                    break;
                case  144:
                    fprintf(arquivoTXT, "%03d: JN  %03d\n", i, cpu.memoria[i+1]);
                    i += 2;
                    break;
                case  160:
                    fprintf(arquivoTXT, "%03d: JZ  %03d\n", i, cpu.memoria[i+1]);
                    i += 2;
                    break;
                case  240:
                    fprintf(arquivoTXT, "%03d: HLT\n", i);
                    i += 1;
                    break;
                default:
                    fprintf(arquivoTXT, "%03d: %03d\n", i, opcode);
                    i += 1;
                    break;
            }
        } else {
            if (opcode == 96) fprintf(arquivoTXT, "%03d: NOT\n", i);
            else if (opcode == 240) fprintf(arquivoTXT, "%03d: HLT\n", i);
            else fprintf(arquivoTXT, "%03d: %03d\n", i, opcode);
            i += 1;
        }
    }
    printMemoryVARS(cpu, arquivoTXT);
    printf("Arquivo de texto exportado!\n");
}