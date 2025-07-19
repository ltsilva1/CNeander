#include "../include/memory.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clearMemory(Neander* cpu) {
    memset(cpu->memoria, 0, sizeof(cpu->memoria));
    memset(cpu->assinatura, 0, sizeof(cpu->assinatura));
    cpu->acumulador = 0;
    cpu->pc = 0;
    cpu->zero = 1;
    cpu->negativo = 0;
}

void exportMemory(Neander* cpu, const char nomeArquivo[]) {
    FILE* arquivo = fopen(nomeArquivo, "wb");
    const uint8_t ASSINATURA_NEANDER[] = {03, 78, 68, 82};
    if (arquivo == NULL) {
        printf("Erro na abertura para escrita do arquivo de memória!\n");
        exit(1);
    }

    fwrite(ASSINATURA_NEANDER, sizeof(uint8_t), 4, arquivo);
    fwrite(cpu->memoria, sizeof(uint8_t), 512, arquivo);

    printf("Memoria exportada!\n");

    fclose(arquivo);
}

void loadMemory(Neander* cpu, const char nomeArquivo[]) {
    const uint8_t ASSINATURA_NEANDER[] = {03, 78, 68, 82};
    FILE* arquivo = fopen(nomeArquivo, "rb");

    if (arquivo == NULL) {
        printf("Erro na abertura para leitura do arquivo de memória!\n");
        exit(1);
    }

    size_t bytesLidosAssinatura = fread(cpu->assinatura, sizeof(uint8_t), 4, arquivo);
    if (bytesLidosAssinatura != 4) {
        printf("Erro: Não foi possível ler a assinatura NEANDER de 4 bytes do arquivo.\n");
        fclose(arquivo);
        exit(1);
    }
    if (memcmp(cpu->assinatura, ASSINATURA_NEANDER, 4) != 0) {
        printf("Erro: Assinatura do arquivo inválida!\n");
        fclose(arquivo);
        exit(1);
    }
    else printf("Arquivo de memória NEANDER validado\n");

    size_t bytesLidosMemoria = fread(cpu->memoria, sizeof(uint8_t), 512, arquivo);
    printf("Memória carregada: %s (%d bytes lidos, dados de %d inteiros 16-bit)\n", nomeArquivo, (int)bytesLidosMemoria, (bytesLidosMemoria) / 2);

    fseek(arquivo, 0, SEEK_END);
    long tamanhoArquivo = ftell(arquivo);
    fseek(arquivo, 0, SEEK_SET);

    if (tamanhoArquivo != 516) {
        printf("Aviso: Arquivo tem %ld bytes, esperado 516 bytes\n", tamanhoArquivo);
    }


    if (bytesLidosMemoria != 512) {
        printf("Aviso: Esperados 516 bytes, lidos %d bytes\n", (int)bytesLidosMemoria);
    }

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
        uint8_t opcode = cpu->memoria[cpu->pc];

        switch (opcode) {
            case 16: // STA
            {
                uint8_t endereco = cpu->memoria[cpu->pc + 2];
                cpu->memoria[endereco*2] = cpu->acumulador;
                cpu->memoria[endereco*2 + 1] = 0;

                cpu->pc += 4;
                break;
            }
            case 32: // LDA
            {
                uint8_t endereco = cpu->memoria[cpu->pc + 2];
                cpu->acumulador = cpu->memoria[endereco*2];

                updateFlags(cpu);

                cpu->pc += 4;
                break;
            }
            case 48: // ADD
            {
                uint8_t endereco = cpu->memoria[cpu->pc + 2];

                uint16_t soma_temporaria = cpu->acumulador + cpu->memoria[endereco*2];
                cpu->acumulador = (uint8_t)soma_temporaria;

                updateFlags(cpu);

                cpu->pc += 4;
                break;
            }
            case 64: // OR
            {
                uint8_t endereco = cpu->memoria[cpu->pc + 2];
                cpu->acumulador |= cpu->memoria[endereco*2];

                updateFlags(cpu);

                cpu->pc += 4;
                break;
            }
            case 80: // AND
            {
                uint8_t endereco = cpu->memoria[cpu->pc + 2];
                cpu->acumulador &= cpu->memoria[endereco*2];

                updateFlags(cpu);

                cpu->pc += 4;
                break;
            }
            case 96: // NOT
            {
                cpu->acumulador = ~cpu->acumulador;

                updateFlags(cpu);

                cpu->pc += 2;
                break;
            }
            case 128: // JMP
            {
                uint8_t endereco = cpu->memoria[cpu->pc + 2];
                cpu->pc = endereco*2;
                break;
            }
            case 144: // JN
            {
                if (cpu->negativo == 1) {
                    uint8_t endereco = cpu->memoria[cpu->pc + 2];
                    cpu->pc = endereco*2;
                } else cpu->pc += 4;
                break;
            }
            case 160: // JZ
            {
                if (cpu->zero == 1) {
                    uint8_t endereco = cpu->memoria[cpu->pc + 2];
                    cpu->pc = endereco*2;
                } else cpu->pc += 4;
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