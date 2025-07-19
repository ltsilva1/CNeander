#ifndef MEMORY_H
#define MEMORY_H
#include <stdint.h>

typedef struct {
    uint8_t memoria[512];
    uint32_t assinatura[4];
    uint8_t acumulador;
    uint8_t pc;
    uint8_t zero;
    uint8_t negativo;
} Neander;

void clearMemory(Neander* cpu);
void exportMemory(Neander* cpu, const char nomeArquivo[]);
void loadMemory(Neander* cpu, const char nomeArquivo[]);
void updateFlags(Neander* cpu);
void executeMemory(Neander* cpu);

#endif //MEMORY_H
