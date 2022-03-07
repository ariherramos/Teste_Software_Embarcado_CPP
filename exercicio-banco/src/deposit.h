#ifndef deposit_h
#define deposit_h

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// A funcao deposit() real deve satisfazer os requisitos
// 1. Aceitar deposito somente se a conta eh valida
// 2. Somente aceitar valores maiores que 100
// 3. Nao aceitar deposito no banco WEG
int deposit(int money, const char* bank);


#endif
