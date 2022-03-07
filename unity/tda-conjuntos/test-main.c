#include "unity.h"
#include "conjunto_interface.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <limits.h> 

void setUp(void) { 
// set stuff up here 
} 
 
void tearDown(void) { 
// clean stuff up here 
}
 
void test_conjunto_cria_e_destroi(void) { 
	conjunto_t *a = conjunto_cria();
	TEST_ASSERT_NOT_NULL(a);
	conjunto_destroi(&a);
	TEST_ASSERT_NULL(a);
	conjunto_destroi(NULL);
}


void test_conjunto_inicializa_vazio(void) { 
    conjunto_t *a = conjunto_cria();
	TEST_ASSERT_NOT_NULL(a);
	conjunto_inicializa_vazio(a);
	TEST_ASSERT_EQUAL_INT(0, conjunto_numero_elementos(a));
	conjunto_inicializa_vazio(NULL);
	conjunto_destroi(&a);
	TEST_ASSERT_NULL(a);
} 

void test_conjunto_insere_e_remove(void) {
	unsigned int numeros = rand() % 100 + 1;
	conjunto_t *a = conjunto_cria();
	TEST_ASSERT_NOT_NULL(a);
	conjunto_inicializa_vazio(a);
	TEST_ASSERT_EQUAL_INT(0, conjunto_numero_elementos(a));

	if(numeros < 10)
		numeros *= 10;

	int *n = (int *) malloc(sizeof(int) * numeros);

	for(int i = 0; i < numeros; i++) {
		n[i] = rand() % INT_MAX + 1;
		TEST_ASSERT_EQUAL_INT(1, conjunto_insere_elemento(n[i], a));
		TEST_ASSERT_EQUAL_INT(1, conjunto_membro(n[i], a));
	}

	for(int i = 0; i < numeros; i++) {
		conjunto_remove_elemento(n[i], a);
		TEST_ASSERT_EQUAL_INT(0, conjunto_membro(n[i], a));		
	}

	free(n);
	conjunto_destroi(&a);

	conjunto_insere_elemento(10, NULL);
	conjunto_remove_elemento(10, NULL);
}

void test_conjunto_diferenca(void) { 
	int numeros1 = 0;
	int numeros2 = 0;
	conjunto_t *a = conjunto_cria();
	conjunto_t *b = conjunto_cria();
	conjunto_t *c = conjunto_cria();
	conjunto_t *d = conjunto_cria();
	TEST_ASSERT_NOT_NULL(a);
	TEST_ASSERT_NOT_NULL(b);
	TEST_ASSERT_NOT_NULL(c);
	TEST_ASSERT_NOT_NULL(d);
	conjunto_inicializa_vazio(a);
	conjunto_inicializa_vazio(b);
	conjunto_inicializa_vazio(c);
	conjunto_inicializa_vazio(d);


	numeros1 = rand() % 100 + 1;
	numeros2 = rand() % 100 + 1;
	
	int *n1 = (int *) malloc(sizeof(int) * numeros1);
	int *n2 = (int *) malloc(sizeof(int) * numeros2);

	for(int i = 0; i < numeros1; i++) {
		n1[i] = rand() % INT_MAX;
		TEST_ASSERT_EQUAL_INT(1, conjunto_insere_elemento(n1[i], a));
		TEST_ASSERT_EQUAL_INT(1, conjunto_membro(n1[i], a));
		TEST_ASSERT_EQUAL_INT(1, conjunto_insere_elemento(n1[i], d));
		TEST_ASSERT_EQUAL_INT(1, conjunto_membro(n1[i], d));
	}

	for(int i = 0; i < numeros2; i++) {
		n2[i] = rand() % INT_MAX;
		TEST_ASSERT_EQUAL_INT(1, conjunto_insere_elemento(n2[i], b));
		TEST_ASSERT_EQUAL_INT(1, conjunto_membro(n2[i], b));
		TEST_ASSERT_EQUAL_INT(1, conjunto_insere_elemento(n2[i], d));
		TEST_ASSERT_EQUAL_INT(1, conjunto_membro(n2[i], d));
	}

	conjunto_diferenca(d, a, c);
	TEST_ASSERT_EQUAL_INT(1, conjunto_igual(b, c));

	conjunto_diferenca(d, b, c);
	TEST_ASSERT_EQUAL_INT(1, conjunto_igual(a, c));

	conjunto_diferenca(d, a, NULL);
	conjunto_diferenca(d, NULL, c);
	conjunto_diferenca(NULL, a, c);

	free(n1);
	free(n2);
	conjunto_destroi(&a);
	conjunto_destroi(&b);
	conjunto_destroi(&c);
	conjunto_destroi(&d);
}

void test_conjunto_atribui(void) { 
	int numeros1 = 0;
	conjunto_t *a = conjunto_cria();
	conjunto_t *b = conjunto_cria();
	TEST_ASSERT_NOT_NULL(a);
	TEST_ASSERT_NOT_NULL(b);
	conjunto_inicializa_vazio(a);
	conjunto_inicializa_vazio(b);


	numeros1 = rand() % 100 + 1;
	
	int *n1 = (int *) malloc(sizeof(int) * numeros1);

	for(int i = 0; i < numeros1; i++) {
		n1[i] = rand() % INT_MAX;
		TEST_ASSERT_EQUAL_INT(1, conjunto_insere_elemento(n1[i], a));
		TEST_ASSERT_EQUAL_INT(1, conjunto_membro(n1[i], a));
	}

	conjunto_atribui(b, a);
	TEST_ASSERT_EQUAL_INT(1, conjunto_igual(b, a));

	conjunto_atribui(b, NULL);
	conjunto_atribui(NULL, a);

	free(n1);
	conjunto_destroi(&a);
	conjunto_destroi(&b);
}

void test_conjunto_igual(void) { 
	int numeros1 = 0;
	int numeros2 = 0;
	conjunto_t *a = conjunto_cria();
	conjunto_t *b = conjunto_cria();
	conjunto_t *c = conjunto_cria();
	TEST_ASSERT_NOT_NULL(a);
	TEST_ASSERT_NOT_NULL(b);
	TEST_ASSERT_NOT_NULL(c);
	conjunto_inicializa_vazio(a);
	conjunto_inicializa_vazio(b);
	conjunto_inicializa_vazio(c);


	numeros1 = rand() % 100 + 1;
	numeros2 = rand() % 100 + 1;
	
	int *n1 = (int *) malloc(sizeof(int) * numeros1);
	int *n2 = (int *) malloc(sizeof(int) * numeros2);

	for(int i = 0; i < numeros1; i++) {
		n1[i] = rand() % INT_MAX;
		TEST_ASSERT_EQUAL_INT(1, conjunto_insere_elemento(n1[i], a));
		TEST_ASSERT_EQUAL_INT(1, conjunto_membro(n1[i], a));
	}

	for(int i = 0; i < numeros2; i++) {
		n2[i] = rand() % INT_MAX;
		TEST_ASSERT_EQUAL_INT(1, conjunto_insere_elemento(n2[i], b));
		TEST_ASSERT_EQUAL_INT(1, conjunto_membro(n2[i], b));
	}

	conjunto_atribui(c, a);
	TEST_ASSERT_EQUAL_INT(1, conjunto_igual(a, c));
	TEST_ASSERT_EQUAL_INT(0, conjunto_igual(a, b));
	TEST_ASSERT_EQUAL_INT(0, conjunto_igual(c, b));

	conjunto_igual(a, NULL);
	conjunto_igual(NULL, c);

	free(n1);
	free(n2);
	conjunto_destroi(&a);
	conjunto_destroi(&b);
	conjunto_destroi(&c);
}

#define ELEM_MAX INT_MAX
#define ELEM_MIN INT_MIN

void test_conjunto_minimo(void) {
	int numeros1 = 0;
	int numeros2 = 0;
	int min_a = INT_MAX;
	int min_b = INT_MAX;
	conjunto_t *a = conjunto_cria();
	conjunto_t *b = conjunto_cria();
	TEST_ASSERT_NOT_NULL(a);
	TEST_ASSERT_NOT_NULL(b);
	conjunto_inicializa_vazio(a);
	conjunto_inicializa_vazio(b);


	numeros1 = rand() % 100 + 1;
	numeros2 = rand() % 100 + 1;
	
	int *n1 = (int *) malloc(sizeof(int) * numeros1);
	int *n2 = (int *) malloc(sizeof(int) * numeros2);

	for(int i = 0; i < numeros1; i++) {
		n1[i] = rand() % INT_MAX;
		if(n1[i] < min_a)
			min_a = n1[i];
		TEST_ASSERT_EQUAL_INT(1, conjunto_insere_elemento(n1[i], a));
		TEST_ASSERT_EQUAL_INT(1, conjunto_membro(n1[i], a));
	}

	for(int i = 0; i < numeros2; i++) {
		n2[i] = rand() % INT_MAX;
		if(n2[i] < min_b)
			min_b = n2[i];
		TEST_ASSERT_EQUAL_INT(1, conjunto_insere_elemento(n2[i], b));
		TEST_ASSERT_EQUAL_INT(1, conjunto_membro(n2[i], b));
	}

	TEST_ASSERT_EQUAL_INT(min_a, conjunto_minimo(a));
	TEST_ASSERT_EQUAL_INT(min_b, conjunto_minimo(b));

	TEST_ASSERT_EQUAL_INT(ELEM_MAX, conjunto_minimo(NULL));

	free(n1);
	free(n2);
	conjunto_destroi(&a);
	conjunto_destroi(&b);
}

void test_conjunto_maximo(void) {
	int numeros1 = 0;
	int numeros2 = 0;
	int max_a = INT_MIN;
	int max_b = INT_MIN;
	conjunto_t *a = conjunto_cria();
	conjunto_t *b = conjunto_cria();
	TEST_ASSERT_NOT_NULL(a);
	TEST_ASSERT_NOT_NULL(b);
	conjunto_inicializa_vazio(a);
	conjunto_inicializa_vazio(b);


	numeros1 = rand() % 100 + 1;
	numeros2 = rand() % 100 + 1;
	
	int *n1 = (int *) malloc(sizeof(int) * numeros1);
	int *n2 = (int *) malloc(sizeof(int) * numeros2);

	for(int i = 0; i < numeros1; i++) {
		n1[i] = rand() % INT_MAX;
		if(n1[i] > max_a)
			max_a = n1[i];
		TEST_ASSERT_EQUAL_INT(1, conjunto_insere_elemento(n1[i], a));
		TEST_ASSERT_EQUAL_INT(1, conjunto_membro(n1[i], a));
	}

	for(int i = 0; i < numeros2; i++) {
		n2[i] = rand() % INT_MAX;
		if(n2[i] > max_b)
			max_b = n2[i];
		TEST_ASSERT_EQUAL_INT(1, conjunto_insere_elemento(n2[i], b));
		TEST_ASSERT_EQUAL_INT(1, conjunto_membro(n2[i], b));
	}

	TEST_ASSERT_EQUAL_INT(max_a, conjunto_maximo(a));
	TEST_ASSERT_EQUAL_INT(max_b, conjunto_maximo(b));

	TEST_ASSERT_EQUAL_INT(ELEM_MIN, conjunto_maximo(NULL));

	free(n1);
	free(n2);
	conjunto_destroi(&a);
	conjunto_destroi(&b);
}

int main(void) { 
	UNITY_BEGIN();
	srand(time(NULL));
	RUN_TEST(test_conjunto_cria_e_destroi);
	RUN_TEST(test_conjunto_inicializa_vazio);
	RUN_TEST(test_conjunto_insere_e_remove);
	RUN_TEST(test_conjunto_diferenca);
	RUN_TEST(test_conjunto_atribui);
	RUN_TEST(test_conjunto_igual);
	RUN_TEST(test_conjunto_minimo);
	RUN_TEST(test_conjunto_maximo);
	return UNITY_END(); 
}

