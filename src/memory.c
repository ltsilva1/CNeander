#include "../include/memory.h"
#include "../include/memory.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "print_functions.h"

void convertMemory(Neander* cpu) {
    for (int i = 0; i < 256; i++)
        cpu->memoria[i] = cpu->buffer[i];
}

void reConvertMemory(Neander* cpu) {
    for (int i = 0; i < 256; i++)
        cpu->buffer[i] = cpu->memoria[i];

}

void clearMemory(Neander* cpu) {
    memset(cpu->memoria, 0, sizeof(cpu->memoria));
    memset(cpu->assinatura, 0, sizeof(cpu->assinatura));
    cpu->acumulador = 0;
    cpu->pc = 0;
    cpu->zero = 1;
    cpu->negativo = 0;
}

void exportMemory(Neander* cpu, const char nomeArquivo[]) { // Not updated yet!
    FILE* arquivo = fopen(nomeArquivo, "wb");
    const uint16_t ASSINATURA_NEANDER[] = {0x4E03, 0x5244};
    if (arquivo == NULL) {
        printf("Erro na abertura para escrita do arquivo de memória!\n");
        exit(1);
    }

    reConvertMemory(cpu);

    fwrite(ASSINATURA_NEANDER, sizeof(uint16_t), 2, arquivo);
    fwrite(cpu->buffer, sizeof(uint16_t), 256, arquivo);

    printf("Memoria exportada!\n");

    printToTxt(*cpu, nomeArquivo);

    fclose(arquivo);
}

void loadMemory(Neander* cpu, const char nomeArquivo[]) {
    const uint16_t ASSINATURA_NEANDER[] = {0x4E03, 0x5244};
    FILE* arquivo = fopen(nomeArquivo, "rb");

    if (arquivo == NULL) {
        printf("Erro na abertura para leitura do arquivo de memória!\n");
        exit(1);
    }

    size_t bytesLidosAssinatura = fread(cpu->assinatura, sizeof(uint16_t), 2, arquivo);
    if (bytesLidosAssinatura != 2) {
        printf("Erro: Não foi possível ler a assinatura NEANDER de 4 bytes do arquivo.\n");
        fclose(arquivo);
        exit(1);
    }
    if (memcmp(cpu->assinatura, ASSINATURA_NEANDER, 2) != 0) {
        printf("Erro: Assinatura do arquivo inválida!\n");
        fclose(arquivo);
        exit(1);
    }
    else printf("Arquivo de memória NEANDER validado\n");

    size_t bytesLidosMemoria = fread(cpu->buffer, sizeof(uint16_t), 256, arquivo);
    printf("Memória carregada: %s (%d bytes lidos, dados de %d inteiros 8-bit)\n", nomeArquivo, (int)bytesLidosMemoria, (bytesLidosMemoria) / 2);

    fseek(arquivo, 0, SEEK_END);
    long tamanhoArquivo = ftell(arquivo);
    fseek(arquivo, 0, SEEK_SET);

    if (tamanhoArquivo != 516) {
        printf("Aviso: Arquivo tem %ld bytes, esperado 516 bytes\n", tamanhoArquivo);
    }

    if (bytesLidosMemoria != 256) {
        printf("Aviso: Esperados 256 bytes, lidos %d bytes\n", (int)bytesLidosMemoria);
    }

    convertMemory(cpu);

    fclose(arquivo);

}

void loadMemoryTMP(Neander* cpu, const char nomeArquivo[]) {
    FILE* arquivo = fopen(nomeArquivo, "rb");

    fread(cpu->buffer, sizeof(uint16_t), 256, arquivo);
    for (int i = 0; i < 256; i++)
        printf("%d ", cpu->buffer[i]);

    fclose(arquivo);
}

void updateFlags(Neander* cpu) {
    if (cpu->acumulador == 0)
        cpu->zero = 1;
    else cpu->zero = 0;

    if (cpu->acumulador >= 128)
        cpu->negativo = 1;
    else cpu->negativo = 0;
}

void executeMemory(Neander* cpu) {
    printf("Executando memoria...\n");
    while (1) {
        //printf("PC: %03d OP: %03d AC: %03d Z: %d N: %d\n", cpu->pc, cpu->memoria[cpu->pc], cpu->acumulador, cpu->zero, cpu->negativo);
        if (cpu->pc >= 256) {
            printf("\nERRO FATAL: O Program Counter saiu dos limites da memória (%d).\n", cpu->pc);
            printf("Execução abortada para prevenir um crash.\n");
            return;
        }

        uint8_t opcode = cpu->memoria[cpu->pc];

        switch (opcode) {
            case 16: // STA
            {
                uint8_t endereco = cpu->memoria[cpu->pc + 1];
                cpu->memoria[endereco] = cpu->acumulador;

                cpu->pc += 2;
                break;
            }
            case 32: // LDA
            {
                uint8_t endereco = cpu->memoria[cpu->pc + 1];
                cpu->acumulador = cpu->memoria[endereco];

                updateFlags(cpu);

                cpu->pc += 2;
                break;
            }
            case 48: // ADD
            {
                uint8_t endereco = cpu->memoria[cpu->pc + 1];

                uint16_t soma_temporaria = cpu->acumulador + cpu->memoria[endereco];
                cpu->acumulador = (uint8_t)soma_temporaria;

                updateFlags(cpu);

                cpu->pc += 2;
                break;
            }
            case 64: // OR
            {
                uint8_t endereco = cpu->memoria[cpu->pc + 1];
                cpu->acumulador |= cpu->memoria[endereco];

                updateFlags(cpu);

                cpu->pc += 2;
                break;
            }
            case 80: // AND
            {
                uint8_t endereco = cpu->memoria[cpu->pc + 1];
                cpu->acumulador &= cpu->memoria[endereco];

                updateFlags(cpu);

                cpu->pc += 2;
                break;
            }
            case 96: // NOT
            {
                cpu->acumulador = ~cpu->acumulador;

                updateFlags(cpu);

                cpu->pc += 1;
                break;
            }
            case 128: // JMP
            {
                uint8_t endereco = cpu->memoria[cpu->pc + 1];
                cpu->pc = endereco;
                break;
            }
            case 144: // JN
            {
                if (cpu->negativo == 1) {
                    uint8_t endereco = cpu->memoria[cpu->pc + 1];
                    cpu->pc = endereco;
                } else cpu->pc += 2;
                break;
            }
            case 160: // JZ
            {
                if (cpu->zero == 1) {
                    uint8_t endereco = cpu->memoria[cpu->pc + 1];
                    cpu->pc = endereco;
                } else cpu->pc += 2;
                break;
            }
            case 240:
                // Não aumenta o PC
                return;
            default:
                printf("???\n");
                return;
        }
    }
}