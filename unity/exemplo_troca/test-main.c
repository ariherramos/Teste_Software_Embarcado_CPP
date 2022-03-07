#include "unity.h"
#include "troca.h"
 
void setUp(void) { 
// set stuff up here 
} 
 
void tearDown(void) { 
// clean stuff up here 
} 
 
void test_function_should_trocar_valor(void) { 
    int a=10,b=20;
    troca(&a,&b);
    TEST_ASSERT_TRUE (a==20);
    TEST_ASSERT_TRUE (b==10);
} 
 
void test_function_should_trocar_valor_msg(void) { 
    int a=10,b=20;
    troca(&a,&b);
    TEST_ASSERT_TRUE_MESSAGE (a==20, "Deve ser 20!");
    TEST_ASSERT_TRUE_MESSAGE (b==10, "Deve ser 10!");
} 
 
int main(void) { 
    UNITY_BEGIN(); 
    RUN_TEST(test_function_should_trocar_valor); 
    RUN_TEST(test_function_should_trocar_valor_msg); 
    return UNITY_END(); 
} 
 
/*
 case=Fila Vazia 2
output = /OK.\].TesteFila.FilaVazia2/i

case=InsereElemento
output =/OK.].TesteFila.InsereElemento/i
 */
