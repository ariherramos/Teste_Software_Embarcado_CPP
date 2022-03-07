#include <stdarg.h>
#include <stdint.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "deposit.h"

int __wrap_deposit(int money, const char* bank)
{
    /*
        Escreva aqui o codigo para testar as condicoes definidas pela funcao deposit():
        1. Aceitar deposito somente se a conta eh valida
        2. Somente aceitar valores maiores que 100
        3. Nao aceitar deposito no banco WEG

        Comece testando os parametros money e bank com check_expected e check_expected_ptr

        Depois utilize mock_type e mock_ptr_type para receber os argumentos passados pelos testes para 
        testar as 3 condicoes.

        retorne EXIT_FAILURE ou EXIT_SUCCESS
    
     */
   
    return EXIT_SUCCESS;
}

