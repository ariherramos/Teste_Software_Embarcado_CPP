#include "pilha_privado.h"
#include <stdlib.h>
#include <string.h>

// Coloque aqui a implementacao das funcoes do TDA pilha generico

/*
 * Cria uma pilha com capacidade "cap" e a inicializa como pilha vazia. "tam_elemento" representa o tamanho de um elemento armazenado dentro da pilha.
 * "imp" eh um ponteiro para uma funcao de impressao dos dados armazenados dentro da pilha. Deve ser usado em "pilha_imprime"
 * Pre: "cap" e "tam_elemento" devem ser valores validos
 * Pos: Retorna um ponteiro para uma pilha vazia se houver memaria disponivel
 */
pilha_t *pilha_cria(int cap, int tam_elemento, void (*imp)(const void *))
{
	if(cap <= 0 || tam_elemento <= 0)
		return NULL;
	pilha_t *p = malloc(sizeof(pilha_t));
	if(p == NULL)
		return NULL;
	p->elementos = malloc(cap * tam_elemento);
	if(p->elementos == NULL)
		return NULL;
	p->capacidade = cap;
	p->tamanho_elemento = tam_elemento;
	p->topo = 0;
	p->imprime = imp;

    //vazamento de memoria
    int *tmp = malloc(10 * sizeof(int));

	return p;
}

/*
 * Destroi a pilha especificada em "p". Nenhuma operacao eh permitida apos a funcao, a nao ser que pilha cria seja chamada novamente. 
 * Pre: "p" deve ser uma pilha valida criada previamente atraves da funcao pilha cria
 * Pos: os recursos da pilha foram liberados com sucesso e a pilha "p" torna-se nula
 */
void pilha_destroi(pilha_t **p)
{
	if(p == NULL)
		return;
	free((*p)->elementos);
	free(*p);
	*p = NULL;
}

/*
 * Retorna 1 se a pilha estiver vazia, 0 caso contrario
 * Pre: a pilha deve existir
 * Pos: retorna 1 caso a pilha estiver vazia, 0 se nao estiver. Retorna -1 caso a pilha nao existir
 */
int pilha_vazia(pilha_t *p)
{
	if(p == NULL) return -1;
	if(p->topo == 0) return 1;
	return 0;
}

/*
 * Retorna 1 se a pilha estiver cheia, 0 caso contrario
 * Pre: a pilha deve existir
 * Pos: retorna 1 caso a pilha estiver cheia, 0 se nao estiver. Retorna -1 caso a pilha nao existir
 */
int pilha_cheia(pilha_t *p)
{
	if(p == NULL) return -1;
	if(p->topo == p->capacidade) return 1;
	return 0;
}

/*
 * Retorna o tamanho da pilha
 * Pre: a pilha deve existir
 * Pos: retorna o tamanho da pilha. Retorna -1 caso a pilha nao existir
 */
int pilha_tamanho(pilha_t *p)
{
	if(p == NULL) return -1;
	return p->topo;
}

/*
 * Empilha um novo elemento na pilha. O conteudo de "elem" eh copiado para dentro da pilha. Retorna 1 caso conseguir empilhar, 0 caso contrario
 * Pre: a pilha deve existir, nao deve estar cheia e "elem" deve ser valido
 * Pos: o elemento recebido pela operacao eh armazenado no topo da pilha
 */
int pilha_empilha(pilha_t *p, void *elem)
{
	if(p == NULL || elem == NULL) return 0;
	if(pilha_cheia(p)) return 0;
	char *a = (char *) p->elementos;
	memcpy(&a[p->topo * p->tamanho_elemento], elem, p->tamanho_elemento);
	p->topo++;
	return 1;
}

/*
 * Desempilha o elemento que estiver no topo da pilha e retorna o seu valor em "elem". Retorna 1 caso conseguir desempilhar, 0 caso contrario
 * Pre: a pilha deve existir e nao deve estar vazia. "elem" deve ser valido
 * Pos: a pilha tera um elemento a menos e o valor do antigo topo eh retornado
 */
int pilha_desempilha(pilha_t *p, void *elem)
{
	if(p == NULL || elem == NULL) return 0;
	if(pilha_vazia(p)) return 0;
	char *a = (char *) p->elementos;
	memcpy(elem, &a[(p->topo - 1) * p->tamanho_elemento], p->tamanho_elemento);
	p->topo--;
	return 1;
}

/*
 * Retorna o valor do elemento no topo da pilha em "elem". Retorna 1 caso a pilha ter um valor em seu topo, 0 caso contrario
 * Pre: a pilha deve existir e nao deve estar vazia. "elem" deve ser valido
 * Pos: o valor do elemento do topo eh retornado em uma variavel
 */
int pilha_topo(pilha_t *p, void *elem)
{
	if(p == NULL || elem == NULL) return 0;
	if(pilha_vazia(p)) return 0;
	char *a = (char *) p->elementos;
	memcpy(elem, &a[(p->topo - 1) * p->tamanho_elemento], p->tamanho_elemento);
	return 1;
}

/*
 * Imprime os elementos da pilha atraves do ponteiro de funcao "imprime", comecando pelo topo da pilha
 * Pre: a pilha deve existir e o ponteiro "imprime" deve ser valido
 * Pos: Os elementos sao impressos usando o ponteiro "imprime"
 */
void pilha_imprime(pilha_t *p)
{
	if(p == NULL) return;

	if(p->imprime == NULL) return;
	
	pilha_t * aux = pilha_cria(p->capacidade, p->tamanho_elemento, p->imprime);
	if(aux == NULL) return;
	
	void *x = malloc(p->tamanho_elemento);
	if(x == NULL) return;

	while(!pilha_vazia(p)) {
		pilha_desempilha(p, x);
		p->imprime(x);
		pilha_empilha(aux, x);
	}
	
	while(!pilha_vazia(aux)) {
		pilha_desempilha(aux, x);		
		pilha_empilha(p, x);
	}

	free(x);
	pilha_destroi(&aux);
}


