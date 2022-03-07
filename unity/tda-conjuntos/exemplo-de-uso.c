#include "conjunto_interface.h"
#include <stdio.h>

int main(void)
{
	conjunto_t *a = conjunto_cria();
	
	if(a == NULL) {
		printf("Conjunto a nao criado\n");
		return 0;
	}

	conjunto_t *b = conjunto_cria();
	if(b == NULL) {
		printf("Conjunto b nao criado\n");
		return 0;
	}

	conjunto_t *c = conjunto_cria();
	if(c == NULL) {
		printf("Conjunto b nao criado\n");
		return 0;
	}

	for(int i = 0; i < 12; i++) {
		printf("Inserindo elemento %d em a\n", i);
		conjunto_insere_elemento(i, a);
	}

	printf("Inserindo elemento %d em a\n", 10);
	conjunto_insere_elemento(10, a);
	printf("Inserindo elemento %d em a\n", 100);
	conjunto_insere_elemento(100, a);

	conjunto_imprime(a);

	printf("Inserindo elemento %d em b\n", 1000);
	conjunto_insere_elemento(1000, b);

	printf("Removendo elemento %d de a\n", 100);
	conjunto_remove_elemento(100, a);

	conjunto_imprime(a);
	conjunto_imprime(b);
	printf("A == B? %d\n", conjunto_igual(a, b));

	conjunto_atribui(c, a);
	conjunto_imprime(c);

	conjunto_uniao(a, b, c);
	conjunto_imprime(c);

	conjunto_diferenca(b, a, c);
	conjunto_imprime(c);
	
	printf("Destruindo conjuntos\n");

	conjunto_destroi(&a);
	conjunto_destroi(&b);
	conjunto_destroi(&c);

	return 0;
}
