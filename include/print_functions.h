//
// Created by lucas on 19/07/25.
//

#ifndef PRINT_FUNCTIONS_H
#define PRINT_FUNCTIONS_H
#include <stdio.h>

#include "memory.h"

void printMemory(Neander cpu);
void printMemoryVARS(Neander cpu, FILE* arq);
void printMemoryASIS(Neander cpu);
void printStates(Neander cpu);
void printToTxt(Neander cpu, const char nomeArquivo[]);

#endif //PRINT_FUNCTIONS_H
