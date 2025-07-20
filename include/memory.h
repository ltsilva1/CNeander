#ifndef MEMORY_H
#define MEMORY_H
#include <stdint.h>

typedef struct {
    uint16_t buffer[256];
    uint8_t memoria[256];
    uint16_t assinatura[4];
    uint8_t acumulador;
    uint8_t pc;
    uint8_t zero;
    uint8_t negativo;
} Neander;

void clearMemory(Neander* cpu);
void exportMemory(Neander* cpu, const char nomeArquivo[]);
void loadMemory(Neander* cpu, const char nomeArquivo[]);
void loadMemoryTMP(Neander* cpu, const char nomeArquivo[]);
void convertMemory(Neander* cpu);
void updateFlags(Neander* cpu);
void executeMemory(Neander* cpu);

#endif //MEMORY_H
