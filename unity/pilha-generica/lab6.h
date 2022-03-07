#ifndef lab6_h
#define lab6_h

#include <stdio.h>
#include "pilha_interface.h"

typedef struct carro {
	unsigned int manobras;
	char placa[8];
} carro_t;

void estacionamento(const char *arquivo, void (*entrada)(carro_t *), void (*saida)(carro_t *));

#endif
