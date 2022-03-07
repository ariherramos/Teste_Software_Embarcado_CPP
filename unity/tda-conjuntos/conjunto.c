#include "conjunto_privado.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*
 * Retorna um ponteiro para conjunto recem criado com espaco para armazenar inicialmente 10 elementos
 * Pre-condicao: o sistema deve ter memoria para alocar o novo conjunto
 * Pos-condicao: o novo conjunto eh retornado
 */
conjunto_t *conjunto_cria(void)
{
	conjunto_t *c = (conjunto_t *) malloc(sizeof(conjunto_t));
	
	if(c == NULL)
		return NULL;

	c->vetor = (elem_t *) malloc(sizeof(elem_t) * ELEMENTOS);

	if(c->vetor == NULL)
		return NULL;

	c->capacidade = ELEMENTOS;
	//printf("Retornando conjunto criado %p, vetor %p, capacidade %d\n", c, c->vetor, c->capacidade); 
	return c;
}

/*
 * Destroi o conjunto "a"
 * Pre-condicao: o conjunto "a" deve ter sido previamente criado com a operacao "cria_conjunto"
 * Pos-condicao: o conjunto passado por parametro nao eh mais valido e nao podera mais ser utilizado
 */
void conjunto_destroi(conjunto_t **a)
{
	if(a) {
		free((*a)->vetor);
		free(*a);
		*a = NULL;
	}
}

/*
 * Retorna o numero de elementos que estao no conjunto "a"
 * Pre-condicao: o conjunto "a" deve ter sido previamente criado com a operacao "cria_conjunto"
 * Pos-condicao: 
 */
int conjunto_numero_elementos(conjunto_t *a)
{
	if(!a)
		return a->numero;
	return 0;
}

/*
 * Recebe um conjunto como parametro e o inicializa como conjunto vazio
 * Pre-condicao: o conjunto "a" deve ser um conjunto criado previamente pela operacao "cria_conjunto"
 * Pos-condicao: o conjunto "a" passara a ser um conjunto vazio
 */
void conjunto_inicializa_vazio(conjunto_t *a)
{
	if(!a) return;
  	a->numero = 0;
}

/*
 * Recebe os conjuntos "a e "b" e retorna a uniao entre eles no conjunto "c"
 * Pre-condicao: os conjuntos "a", "b" e "c" devem ser conjuntos validos
 * Pos-condicao: o conjunto "c" contera a uniao entre os conjuntos "a" e "b"
 */
void conjunto_uniao(conjunto_t *a, conjunto_t *b, conjunto_t *c)
{
	if(!(a && b && c)) return;

	conjunto_inicializa_vazio(c);

	for(int i = 0; i < a->numero; i++) {
		conjunto_insere_elemento(a->vetor[i], c);
	}

	for(int i = 0; i < b->numero; i++) {
		conjunto_insere_elemento(b->vetor[i], c);
	}
}

/*
 * Recebe os conjuntos "a e "b" e retorna a interseccao entre eles no conjunto "c"
 * Pre-condicao: os conjuntos "a", "b" e "c" devem ser conjuntos validos
 * Pos-condicao: o conjunto "c" contera a interseccao entre os conjuntos "a" e "b"
 */
void conjunto_interseccao(conjunto_t *a, conjunto_t *b, conjunto_t *c)
{
	if(!(a && b && c)) return;
	
	conjunto_inicializa_vazio(c);

	for(int i = 0; i < a->numero; i++) {
		if(conjunto_membro(a->vetor[i], b))
	  		conjunto_insere_elemento(a->vetor[i], c);
	}
}

/*
 * Recebe os conjuntos "a" e "b" e retorna a diferenca entre eles no conjunto "c"
 * Pre-condicao: os conjuntos "a", "b" e "c" devem ser conjuntos validos, criados pela operacao "cria_conjunto"
 * Pos-condicao: o conjunto "c" contera a diferenca entre os conjuntos "a" e "b"
 */
void conjunto_diferenca(conjunto_t *a, conjunto_t *b, conjunto_t *c)
{
	if(!(a && b && c)) return;
	
	conjunto_inicializa_vazio(c);

	for(int i = 0; i < a->numero; i++) {
		if(!conjunto_membro(a->vetor[i], b))
	  		conjunto_insere_elemento(a->vetor[i], c);
	}
}

/*
 * Retorna 1 se o elemento "x" pertence ao conjunto "a", 0 caso contrario
 * Pre-condicao: o conjunto A deve ser um conjunto criado previamente pela operacao "cria_conjunto"
 * Pos-condicao: o valor retornado sera 0 ou 1
 */
int conjunto_membro(elem_t x, conjunto_t *a)
{
	if(!a) return 0;
  
	for(int i = 0; i < a->numero; i++) {
		if(a->vetor[i] == x)
	  		return 1;
	}
	return 0;
}

/*
 * Insere o elemento "x" no conjunto "a". Se "x" ja pertencer a "a" nao faz nada (retorna 1 nesse caso). Retorna 1 caso inseriu corretamente, 0 caso contrario.
 * Pre-condicao: o conjunto "a" deve ser um conjunto criado previamente pela operacao "cria_conjunto"
 * Pos-condicao: o elemento "x" passara a pertencer ao conjunto "a"
 */
int conjunto_insere_elemento(elem_t x, conjunto_t *a)
{
	if(!a) return 0;
 	if(conjunto_membro(x, a)) return 1;

	if(a->numero == a->capacidade) {
		a->capacidade += ELEMENTOS;
		a->vetor = (elem_t *) realloc((void *) a->vetor, a->capacidade * sizeof(elem_t));
		if(a->vetor == NULL) {
			return 0;
		}	
	}  

	a->vetor[a->numero] = x;
	a->numero++;
	return 1;
}

/*
 * Remove o elemento "x" no conjunto "a". Se "x" nao pertencer a "a", nao faz nada
 * Pre-condicao: o conjunto "a" deve ser um conjunto criado previamente pela operacao "cria_conjunto"
 * Pos-condicao: o conjunto "a" passara a nao ter mais o elemento "x"
 */
void conjunto_remove_elemento(elem_t x, conjunto_t *a)
{
	if(!a) return;
	if(!conjunto_membro(x, a)) return;
	for(int i = 0; i < a->numero; i++) {
		if(a->vetor[i] == x) {
			//printf("Removendo %d do conjunto %p, indice %d\n", x, a, i);
	  		conjunto_desloca_elementos(a, i);
		}
	}
}

/*
 * Atribui o conjunto "a" ao "b" (a = b)
 * Pre-condicao: os conjuntos "a" e "b" devem ser conjuntos criados previamente pela operacao "cria_conjunto"
 * Pos-condicao: 
 */
void conjunto_atribui(conjunto_t *a, conjunto_t *b)
{
	if(!(a && b)) return;

	conjunto_inicializa_vazio(a);
	
	if(b->capacidade > a->capacidade) {
		a->vetor = (elem_t *) realloc((void *) a->vetor, b->capacidade * sizeof(elem_t));
	}

	a->capacidade = b->capacidade;

	for(int i = 0; i < b->numero; i++) {
		if(!conjunto_membro(b->vetor[i], a))
			conjunto_insere_elemento(b->vetor[i], a);
	}

	a->numero = b->numero;
}

/*
 * Retorna 1 caso o conjunto "a" seja igual ao conjunto "b", 0 caso contrario
 * Pre-condicao: os conjuntos "a" e "b" devem ser conjuntos criados previamente pela operacao "cria_conjunto"
 * Pos-condicao: 
 */
int conjunto_igual(conjunto_t *a, conjunto_t *b)
{
	if(!(a && b)) return 0;
  
	for(int i = 0; i < a->numero; i++) {
		if(!conjunto_membro(a->vetor[i], b))
			return 0;
	}

	for(int i = 0; i < b->numero; i++) {
		if(!conjunto_membro(b->vetor[i], a))
	  		return 0;
	}

	return 1;
}

/*
 * Retorna o valor minimo dentro do conjunto "a", retorne ELEM_MAX caso erro.
 * Pre-condicao: o conjunto "a" deve ser um conjunto criado previamente pela operacao "cria_conjunto"
 * Pos-condicao: 
 */
elem_t conjunto_minimo(conjunto_t *a)
{
	if(!a) return ELEM_MAX;
	elem_t min = ELEM_MAX;

	for(int i = 0; i < a->numero; i++) {
		if(a->vetor[i] < min)
	  		min = a->vetor[i];
	}

	return min;
}

/*
 * Retorna o valor maximo dentro do conjunto "a", retorne ELEM_MIN caso erro.
 * Pre-condicao: o conjunto "a" deve ser um conjunto criado previamente pela operacao "cria_conjunto"
 * Pos-condicao: 
 */
elem_t conjunto_maximo(conjunto_t *a)
{
	if(!a) return ELEM_MIN;
	elem_t max = ELEM_MIN;

	for(int i = 0; i < a->numero; i++) {
		if(a->vetor[i] > max)
	  		max = a->vetor[i];
	}

	return max;
}

/*
 * Imprime o conjunto "a", sendo os elementos separados por espaco. Se for o ultimo elemento, nao deve ser impresso o ultimo espaco. Quebra de linha no final.
 * Pre-condicao: o conjunto "a" deve ser um conjunto criado previamente pela operacao "cria_conjunto"
 * Pos-condicao: 
 */
void conjunto_imprime(conjunto_t *a)
{
	if(!a) return;
  
	for(int i = 0; i < a->numero; i++) {
		if(i == a->numero - 1)
			printf("%d", a->vetor[i]);
		else
			printf("%d ", a->vetor[i]);
	}
	printf("\n");
}

