#include "lab6.h"
#include <stdlib.h>
#include <string.h>

#define PILHA_CAPACIDADE 10

void imprime(const void *t)
{
	carro_t *c = (carro_t *) t;
	printf("%s\n", c->placa);
}

int processa_saida(pilha_t *estacionou, carro_t *c)
{
	pilha_t *manobra = pilha_cria(PILHA_CAPACIDADE, sizeof(carro_t), NULL);
	if(manobra == NULL) return 0;
	
	//printf("Processa saida: %s\n", c->placa);
	//printf("Pilha antes de processar saida:\n");
	//pilha_imprime(estacionou);
	//printf("\n\n\n");

	carro_t tmp;
	int achou = 0;
	while(pilha_vazia(estacionou) == 0) {
		pilha_topo(estacionou, &tmp);
		if(strcmp(tmp.placa, c->placa) == 0) {
			pilha_desempilha(estacionou, &tmp);
			achou = 1;
			break;
		} else {
			pilha_empilha(manobra, &tmp);
			pilha_desempilha(estacionou, &tmp);
		}
	}

	if(achou)
		memcpy(c, &tmp, sizeof(carro_t));

	if(pilha_vazia(estacionou) == 1 && pilha_vazia(manobra) == 0 && achou == 0)
		printf("Carro %s nao esta no estacionamento\n", c->placa);
	else if(pilha_vazia(estacionou) == 1 && pilha_vazia(manobra) == 1 && achou == 0)
		printf("Estacionamento vazio\n");

	while(pilha_vazia(manobra) == 0){
		pilha_desempilha(manobra, &tmp);
        tmp.manobras++;
		pilha_empilha(estacionou, &tmp);
    }

	//printf("Pilha depois de processar saida:\n");
	//pilha_imprime(estacionou);
	//printf("\n\n\n");

	pilha_destroi(&manobra);
	return achou;
}

void estacionamento(const char *arquivo, void (*entrada)(carro_t *), void (*saida)(carro_t*))
{
	pilha_t *estacionar;
	if(arquivo == NULL) return;
	
	FILE *fp = fopen(arquivo, "r");
	if(fp == NULL) return;

	estacionar = pilha_cria(PILHA_CAPACIDADE, sizeof(carro_t), imprime);

	if(estacionar == NULL) return;

	while(!feof(fp)) {
		char comando;
		fscanf(fp, "%c", &comando);

		//printf("Comando = %c ", comando);

		if(comando == 'F')
			break;

		carro_t *c = (carro_t *) malloc(sizeof(carro_t));
		
		fscanf(fp, "%s\n", c->placa);		
		//printf("Placa = %s\n", c->placa);
		c->manobras = 0;

		if(comando == 'E') {
			entrada(c);
			if(pilha_cheia(estacionar)) {
				//printf("ESTACIONAMENTO CHEIO\n");			
				saida(c);
			} else {
				//printf("Empilhando %s\n", c->placa);
				pilha_empilha(estacionar, c);
			}
		} else if(comando == 'S') {
			int achou = processa_saida(estacionar, c);
			if(achou)
				saida(c);
		}
		free(c);
	}

	pilha_destroi(&estacionar);
	fclose(fp);
}

