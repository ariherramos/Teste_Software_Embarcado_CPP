#include "unity.h"
#include "pilha_interface.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <limits.h> 
#include <string.h> 
#include "lab6.h"

#define TAM 100

typedef struct {
	int x;
	float y;
	char v[TAM];
} minha_struct_t;

float reduction=0.0;

void setUp(void) { 
// set stuff up here 
} 
 
void tearDown(void) { 
// clean stuff up here 
}

//se testar = 1, testa a string resultado com a string interna. Retorna o resultado da comparação das duas strings
int adiciona_elemento_vetor(int *dado, int testar, char *resultado)
{
	static char interna[3000];
	static int i = 0;

	if(testar == 0) {
		i += sprintf(interna+i, "%d", *dado);
		interna[i] = '\0';
		return 0;
	}

	if(resultado == NULL)
		return 0;

	return strcmp(interna, resultado);
}

void imprime_int(const void *a)
{
	adiciona_elemento_vetor((int *)a, 0, NULL);
}

void imprime_struct(const void *a)
{

}

void test_pilha_cria_e_destroi(void) { 
	pilha_t *a = pilha_cria(-10, -10, NULL);
	TEST_ASSERT_NULL(a);

	a = pilha_cria(100, sizeof(int), NULL);
	TEST_ASSERT_NOT_NULL(a);
	pilha_destroi(&a);
	TEST_ASSERT_NULL(a);

	a = pilha_cria(100, sizeof(int), imprime_int);
	TEST_ASSERT_NOT_NULL(a);
	pilha_destroi(&a);
	TEST_ASSERT_NULL(a);

	pilha_destroi(NULL);
    reduction += 0.5;
}

void test_pilha_vazia(void) { 
	pilha_t *a = pilha_cria(100, sizeof(int), NULL);
	TEST_ASSERT_NOT_NULL(a);

	TEST_ASSERT_EQUAL_INT(1, pilha_vazia(a));

	unsigned int v = rand() % 1000000;
	pilha_empilha(a, &v);

	TEST_ASSERT_EQUAL_INT(0, pilha_vazia(a));

	pilha_destroi(&a);
	TEST_ASSERT_NULL(a);

	TEST_ASSERT_EQUAL_INT(-1, pilha_vazia(NULL));
    reduction += 0.5;
}

void test_pilha_cheia(void) { 
	pilha_t *a = pilha_cria(1, sizeof(int), NULL);
	TEST_ASSERT_NOT_NULL(a);

	TEST_ASSERT_EQUAL_INT(0, pilha_cheia(a));

	unsigned int v = rand() % 1000000;
	pilha_empilha(a, &v);

	TEST_ASSERT_EQUAL_INT(1, pilha_cheia(a));

	pilha_destroi(&a);
	TEST_ASSERT_NULL(a);

	TEST_ASSERT_EQUAL_INT(-1, pilha_cheia(NULL));
    reduction += 0.5;
}

void test_pilha_tamanho(void) { 
	pilha_t *a = pilha_cria(1, sizeof(int), NULL);
	TEST_ASSERT_NOT_NULL(a);

	TEST_ASSERT_EQUAL_INT(0, pilha_tamanho(a));

	unsigned int v = rand() % 1000000;
	pilha_empilha(a, &v);

	TEST_ASSERT_EQUAL_INT(1, pilha_tamanho(a));

	pilha_destroi(&a);
	TEST_ASSERT_NULL(a);

	TEST_ASSERT_EQUAL_INT(-1, pilha_tamanho(NULL));
    reduction += 0.5;
}

// from http://stackoverflow.com/questions/2509679/how-to-generate-a-random-number-from-within-a-range
unsigned int gera_int_intervalo(unsigned int min, unsigned int max)
{
    int r;
    const unsigned int range = 1 + max - min;
    const unsigned int buckets = RAND_MAX / range;
    const unsigned int limit = buckets * range;

    /* Create equal size buckets all in a row, then fire randomly towards
     * the buckets until you land in one of them. All buckets are equally
     * likely. If you land off the end of the line of buckets, try again. */
    do
    {
        r = rand();
    } while (r >= limit);

    return min + (r / buckets);
}

void gera_string(char *nome)
{
	char *validchars = "abcdefghijklmnopqrstuvwxiz";

	int tamanho = gera_int_intervalo(8, TAM-1);

	for (int i = 0; i < tamanho; i++ ) {
		nome[i] = validchars[rand() % strlen(validchars)];
		nome[i + 1] = 0x0;
	}
}

void test_pilha_empilha(void) {
	const int CAPACIDADE = 10000;

	// inicio teste com inteiros
	pilha_t *p = pilha_cria(CAPACIDADE, sizeof(int), imprime_int);
	TEST_ASSERT_NOT_NULL(p);

	int topo, anterior, valor;

	for(int i = 0; i < CAPACIDADE+1; i++) {
		if(i == 0) {
			TEST_ASSERT_EQUAL_INT(0, pilha_tamanho(p));
			TEST_ASSERT_EQUAL_INT(1, pilha_vazia(p));
			TEST_ASSERT_EQUAL_INT(0, pilha_cheia(p));
		} else {
			if(i == CAPACIDADE) { //ultimo elemento a ser inserido, a pilha deve estar cheia
				TEST_ASSERT_EQUAL_INT(CAPACIDADE, pilha_tamanho(p));
				TEST_ASSERT_EQUAL_INT(1, pilha_cheia(p));
			} else {
				TEST_ASSERT_EQUAL_INT(0, pilha_cheia(p));
				TEST_ASSERT_EQUAL_INT(i, pilha_tamanho(p));
			}
			TEST_ASSERT_EQUAL_INT(0, pilha_vazia(p));
		}

		valor = rand() % 1000000;

		if(i != CAPACIDADE) {
			TEST_ASSERT_EQUAL_INT(1, pilha_empilha(p, (void *) &valor));
			pilha_topo(p, (void *) &topo);
			TEST_ASSERT_EQUAL_INT(valor, topo);
		} else {
			TEST_ASSERT_EQUAL_INT(0, pilha_empilha(p, (void *) &valor));
			pilha_topo(p, (void *) &topo);
			TEST_ASSERT_EQUAL_INT(anterior, topo);
		}
		
		anterior = valor;
	}

	TEST_ASSERT_EQUAL_INT(0, pilha_empilha(p, NULL));

	pilha_destroi(&p);
	TEST_ASSERT_NULL(p);
	TEST_ASSERT_EQUAL_INT(0, pilha_empilha(NULL, (void *) &valor));
	// fim teste com inteiros

	// inicio teste com estrutura
	p = pilha_cria(CAPACIDADE, sizeof(minha_struct_t), imprime_struct);
	TEST_ASSERT_NOT_NULL(p);

	minha_struct_t topo_struct, anterior_struct, valor_struct;

	for(int i = 0; i < CAPACIDADE+1; i++) {
		if(i == 0) {
			TEST_ASSERT_EQUAL_INT(0, pilha_tamanho(p));
			TEST_ASSERT_EQUAL_INT(1, pilha_vazia(p));
			TEST_ASSERT_EQUAL_INT(0, pilha_cheia(p));
		} else {
			if(i == CAPACIDADE) { //ultimo elemento a ser inserido, a pilha deve estar cheia
				TEST_ASSERT_EQUAL_INT(CAPACIDADE, pilha_tamanho(p));
				TEST_ASSERT_EQUAL_INT(1, pilha_cheia(p));
			} else {
				TEST_ASSERT_EQUAL_INT(0, pilha_cheia(p));
				TEST_ASSERT_EQUAL_INT(i, pilha_tamanho(p));
			}
			TEST_ASSERT_EQUAL_INT(0, pilha_vazia(p));
		}

		valor_struct.x = rand() % 1000000;
		valor_struct.y = (float)rand()/(float)(RAND_MAX/ (rand() % RAND_MAX));
		gera_string(valor_struct.v);

		if(i != CAPACIDADE) {
			TEST_ASSERT_EQUAL_INT(1, pilha_empilha(p, (void *) &valor_struct));
			pilha_topo(p, (void *) &topo_struct);
			TEST_ASSERT_EQUAL_INT(valor_struct.x, topo_struct.x);
			TEST_ASSERT_EQUAL_FLOAT(valor_struct.y, topo_struct.y);
			TEST_ASSERT_EQUAL_STRING(valor_struct.v, topo_struct.v);
		} else {
			TEST_ASSERT_EQUAL_INT(0, pilha_empilha(p, (void *) &valor_struct));
			pilha_topo(p, (void *) &topo_struct);
			TEST_ASSERT_EQUAL_INT(anterior_struct.x, topo_struct.x);
			TEST_ASSERT_EQUAL_FLOAT(anterior_struct.y, topo_struct.y);
			TEST_ASSERT_EQUAL_STRING(anterior_struct.v, topo_struct.v);
		}
		
		memcpy(&anterior_struct, &valor_struct, sizeof(minha_struct_t));
	}

	TEST_ASSERT_EQUAL_INT(0, pilha_empilha(p, NULL));

	pilha_destroi(&p);
	TEST_ASSERT_NULL(p);
	TEST_ASSERT_EQUAL_INT(0, pilha_empilha(NULL, (void *) &valor_struct));
	// fim teste com estrutura
    reduction += 2.0;
}

void test_pilha_desempilha(void) { 
	const int CAPACIDADE = 10000;

	int valores[CAPACIDADE];

	// inicio teste com inteiros
	pilha_t *p = pilha_cria(CAPACIDADE, sizeof(int), imprime_int);
	TEST_ASSERT_NOT_NULL(p);

	int topo, anterior;

	for(int i = 0; i < CAPACIDADE+1; i++) {
		if(i == 0) {
			TEST_ASSERT_EQUAL_INT(0, pilha_tamanho(p));
			TEST_ASSERT_EQUAL_INT(1, pilha_vazia(p));
			TEST_ASSERT_EQUAL_INT(0, pilha_cheia(p));
		} else {
			if(i == CAPACIDADE) { //ultimo elemento a ser inserido, a pilha deve estar cheia
				TEST_ASSERT_EQUAL_INT(CAPACIDADE, pilha_tamanho(p));
				TEST_ASSERT_EQUAL_INT(1, pilha_cheia(p));
			} else {
				TEST_ASSERT_EQUAL_INT(0, pilha_cheia(p));
				TEST_ASSERT_EQUAL_INT(i, pilha_tamanho(p));
			}
			TEST_ASSERT_EQUAL_INT(0, pilha_vazia(p));
		}

		if(i != CAPACIDADE) {
			valores[i] = rand() % 1000000;
			TEST_ASSERT_EQUAL_INT(1, pilha_empilha(p, (void *) &valores[i]));
			pilha_topo(p, (void *) &topo);
			TEST_ASSERT_EQUAL_INT(valores[i], topo);
			anterior = valores[i];
		} else {
			TEST_ASSERT_EQUAL_INT(0, pilha_empilha(p, (void *) &valores[i-1]));
			pilha_topo(p, (void *) &topo);
			TEST_ASSERT_EQUAL_INT(anterior, topo);
		}		
	}

	for(int i = CAPACIDADE+1; i >= 0; i--) {
		if(i == 0) {
			TEST_ASSERT_EQUAL_INT(0, pilha_tamanho(p));
			TEST_ASSERT_EQUAL_INT(1, pilha_vazia(p));
			TEST_ASSERT_EQUAL_INT(0, pilha_cheia(p));
			TEST_ASSERT_EQUAL_INT(0, pilha_desempilha(p, (void *) &topo));
		} else if(i == CAPACIDADE+1) {
			TEST_ASSERT_EQUAL_INT(CAPACIDADE, pilha_tamanho(p));
			TEST_ASSERT_EQUAL_INT(0, pilha_vazia(p));
			TEST_ASSERT_EQUAL_INT(1, pilha_cheia(p));
		} else {
			TEST_ASSERT_EQUAL_INT(i, pilha_tamanho(p));
			TEST_ASSERT_EQUAL_INT(0, pilha_vazia(p));
			if(i == CAPACIDADE)
				TEST_ASSERT_EQUAL_INT(1, pilha_cheia(p));
			else 
				TEST_ASSERT_EQUAL_INT(0, pilha_cheia(p));

			TEST_ASSERT_EQUAL_INT(1, pilha_desempilha(p, (void *) &topo));
			TEST_ASSERT_EQUAL_INT(valores[i-1], topo);
		}
	}

	TEST_ASSERT_EQUAL_INT(0, pilha_desempilha(p, NULL));

	pilha_destroi(&p);
	TEST_ASSERT_NULL(p);
	TEST_ASSERT_EQUAL_INT(0, pilha_desempilha(NULL, (void *) &valores[0]));
	// fim teste com inteiros

	// inicio teste com estrutura
	p = pilha_cria(CAPACIDADE, sizeof(minha_struct_t), imprime_struct);
	TEST_ASSERT_NOT_NULL(p);

	minha_struct_t topo_struct, anterior_struct, valores_struct[CAPACIDADE];

	for(int i = 0; i < CAPACIDADE+1; i++) {
		if(i == 0) {
			TEST_ASSERT_EQUAL_INT(0, pilha_tamanho(p));
			TEST_ASSERT_EQUAL_INT(1, pilha_vazia(p));
			TEST_ASSERT_EQUAL_INT(0, pilha_cheia(p));
		} else {
			if(i == CAPACIDADE) { //ultimo elemento a ser inserido, a pilha deve estar cheia
				TEST_ASSERT_EQUAL_INT(CAPACIDADE, pilha_tamanho(p));
				TEST_ASSERT_EQUAL_INT(1, pilha_cheia(p));
			} else {
				TEST_ASSERT_EQUAL_INT(0, pilha_cheia(p));
				TEST_ASSERT_EQUAL_INT(i, pilha_tamanho(p));
			}
			TEST_ASSERT_EQUAL_INT(0, pilha_vazia(p));
		}

		valores_struct[i].x = rand() % 1000000;
		valores_struct[i].y = (float)rand()/(float)(RAND_MAX/ (rand() % RAND_MAX));
		gera_string(valores_struct[i].v);

		if(i != CAPACIDADE) {
			TEST_ASSERT_EQUAL_INT(1, pilha_empilha(p, (void *) &valores_struct[i]));
			pilha_topo(p, (void *) &topo_struct);
			TEST_ASSERT_EQUAL_INT(valores_struct[i].x, topo_struct.x);
			TEST_ASSERT_EQUAL_FLOAT(valores_struct[i].y, topo_struct.y);
			TEST_ASSERT_EQUAL_STRING(valores_struct[i].v, topo_struct.v);
			memcpy(&anterior_struct, &valores_struct[i], sizeof(minha_struct_t));
		} else {
			TEST_ASSERT_EQUAL_INT(0, pilha_empilha(p, (void *) &valores_struct[i]));
			pilha_topo(p, (void *) &topo_struct);
			TEST_ASSERT_EQUAL_INT(anterior_struct.x, topo_struct.x);
			TEST_ASSERT_EQUAL_FLOAT(anterior_struct.y, topo_struct.y);
			TEST_ASSERT_EQUAL_STRING(anterior_struct.v, topo_struct.v);
		}				
	}

	for(int i = CAPACIDADE+1; i >= 0; i--) {
		if(i == 0) {
			TEST_ASSERT_EQUAL_INT(0, pilha_tamanho(p));
			TEST_ASSERT_EQUAL_INT(1, pilha_vazia(p));
			TEST_ASSERT_EQUAL_INT(0, pilha_cheia(p));
			TEST_ASSERT_EQUAL_INT(0, pilha_desempilha(p, (void *) &topo_struct));
		} else if(i == CAPACIDADE+1) {
			TEST_ASSERT_EQUAL_INT(CAPACIDADE, pilha_tamanho(p));
			TEST_ASSERT_EQUAL_INT(0, pilha_vazia(p));
			TEST_ASSERT_EQUAL_INT(1, pilha_cheia(p));
		} else {
			TEST_ASSERT_EQUAL_INT(i, pilha_tamanho(p));
			TEST_ASSERT_EQUAL_INT(0, pilha_vazia(p));
			if(i == CAPACIDADE)
				TEST_ASSERT_EQUAL_INT(1, pilha_cheia(p));
			else 
				TEST_ASSERT_EQUAL_INT(0, pilha_cheia(p));

			TEST_ASSERT_EQUAL_INT(1, pilha_desempilha(p, (void *) &topo_struct));
			TEST_ASSERT_EQUAL_INT(valores_struct[i-1].x, topo_struct.x);
			TEST_ASSERT_EQUAL_FLOAT(valores_struct[i-1].y, topo_struct.y);
			TEST_ASSERT_EQUAL_STRING(valores_struct[i-1].v, topo_struct.v);
		}
	}


	TEST_ASSERT_EQUAL_INT(0, pilha_desempilha(p, NULL));

	pilha_destroi(&p);
	TEST_ASSERT_NULL(p);
	TEST_ASSERT_EQUAL_INT(0, pilha_desempilha(NULL, (void *) &valores_struct[0]));
	// fim teste com estrutura
    reduction += 2.0;
}

void test_pilha_topo(void) { 
	const int CAPACIDADE = 10000;

	// inicio teste com inteiros
	pilha_t *p = pilha_cria(CAPACIDADE, sizeof(int), imprime_int);
	TEST_ASSERT_NOT_NULL(p);

	int topo, anterior, valor;

	for(int i = 0; i < CAPACIDADE+1; i++) {
		valor = rand() % 1000000;

		if(i != CAPACIDADE) {
			TEST_ASSERT_EQUAL_INT(1, pilha_empilha(p, (void *) &valor));
			TEST_ASSERT_EQUAL_INT(1, pilha_topo(p, (void *) &topo));
			TEST_ASSERT_EQUAL_INT(valor, topo);
			anterior = valor;
		} else {
			TEST_ASSERT_EQUAL_INT(0, pilha_empilha(p, (void *) &valor));
			TEST_ASSERT_EQUAL_INT(1, pilha_topo(p, (void *) &topo));
			TEST_ASSERT_EQUAL_INT(anterior, topo);
		}				
	}

	TEST_ASSERT_EQUAL_INT(0, pilha_topo(p, NULL));

	pilha_destroi(&p);
	TEST_ASSERT_NULL(p);
	TEST_ASSERT_EQUAL_INT(0, pilha_topo(NULL, (void *) &valor));
	// fim teste com inteiros

   reduction += 0.5;

}

void inplace_reverse(char * str)
{
  if (str)
  {
    char * end = str + strlen(str) - 1;

    // swap the values in the two given variables
    // XXX: fails when a and b refer to same memory location
#   define XOR_SWAP(a,b) do\
    {\
      a ^= b;\
      b ^= a;\
      a ^= b;\
    } while (0)

    // walk inwards from both ends of the string, 
    // swapping until we get to the middle
    while (str < end)
    {
      XOR_SWAP(*str, *end);
      str++;
      end--;
    }
#   undef XOR_SWAP
  }
}

void test_pilha_imprime(void) { 
	const int CAPACIDADE = 100;
	int valores[CAPACIDADE];
	char resultado[3000];
	int count = 0;
	char tmp[3];
	tmp[2] = '\0';

	// inicio teste com inteiros
	pilha_t *p = pilha_cria(CAPACIDADE, sizeof(int), imprime_int);
	TEST_ASSERT_NOT_NULL(p);

	for(int i = 0; i < CAPACIDADE; i++) {
		valores[i] = rand() % 100;
		if(valores[i] < 10) {
			tmp[0] = (valores[i] % 10) + '0';
			tmp[1] = '\0';
		} else {
			tmp[0] = (valores[i] % 10) + '0';
			tmp[1] = (valores[i] / 10) + '0';
		}		
		//count += sprintf(resultado+count, "%s", tmp);
		strcpy(resultado+count, tmp);
		count += strlen(tmp);
		resultado[count] = '\0';
		//printf("Count = %d - Resultado depois da escrita do valor %d na string = %s\n", count, valores[i], resultado);
		TEST_ASSERT_EQUAL_INT(1, pilha_empilha(p, (void *) &valores[i]));		
	}

	//printf("Antiga = %s\n", resultado);
	inplace_reverse(resultado);
	//printf("Novo = %s\n", resultado);

	pilha_imprime(p);
	TEST_ASSERT_EQUAL_INT(0, adiciona_elemento_vetor(NULL, 1, resultado));

	TEST_ASSERT_EQUAL(0, pilha_vazia(p)); // teste para verificar se a funcao imprime nao corrompeu toda a pilha

	pilha_destroi(&p);
	TEST_ASSERT_NULL(p);
    reduction += 1.0;
}


int main(void) { 
	UNITY_BEGIN();
	srand(time(NULL));
	RUN_TEST(test_pilha_cria_e_destroi);
	RUN_TEST(test_pilha_vazia);
	RUN_TEST(test_pilha_cheia);
	RUN_TEST(test_pilha_tamanho);
	RUN_TEST(test_pilha_empilha);
	RUN_TEST(test_pilha_desempilha);
	RUN_TEST(test_pilha_topo);
	RUN_TEST(test_pilha_imprime);
    int fim = UNITY_END();
    //printf("red: %f\n",reduction);
    float grade = Unity.NumberOfTests-((reduction * (Unity.NumberOfTests-fim))/Unity.NumberOfTests);
	return  (int) grade;
}

