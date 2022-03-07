#ifndef conjunto_privado_h
#define conjunto_privado_h

#include "conjunto_interface.h"
#include <limits.h>

#include <stdio.h>

#define ELEMENTOS 50
#define ELEM_MAX INT_MAX
#define ELEM_MIN INT_MIN

typedef int elem_t;

typedef struct conjunto {
	elem_t *vetor;
	int numero;
	int capacidade;
} conjunto_t;

//Operacoes privadas ao TDA que por ventura sejam necessarias

void conjunto_desloca_elementos(conjunto_t *a, int indice)
{
	//printf("a->vetor[%d] = %d, numero %d, a->vetor[a->numero - 1] = %d\n", indice, a->vetor[indice], a->numero, a->vetor[a->numero - 1]);

	if(indice != (a->numero -1)) {
		a->vetor[indice] = a->vetor[a->numero - 1];
	}
	
	//for(int i = indice; i < a->numero; i++) {
	//	a->v[indice] = a->v[indice + 1];
	//}

	a->numero--;
}

#endif
