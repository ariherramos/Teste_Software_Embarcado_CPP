#include <stdarg.h>
#include <stdint.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "banco.h"

static void test_successful_deposit(void** state)
{
    (void)state;  // unused variable

    /*
        Escreva aqui o codigo de teste.

        Utilize expect_value e expect_string para determinar os valores do parametros que sera testados na mock function com check_*.

        Utilize will_return para passar os valores de teste. Lembre que a ordem e a quantidade que sao passados importam.

        Depois de passar os parametros, chame a funcao production_code e verifique o valor de retorna com 
        assert_int_equal(ret, EXIT_SUCCEESS) ou assert_int_equal(ret, EXIT_FAILURE)
    */

    
}

static void test_failed_deposit(void** state)
{
    (void)state;  //unused variable        

    /*
        Escreva aqui o codigo de teste.

        Utilize expect_value e expect_string para determinar os valores do parametros que sera testados na mock function com check_*.

        Utilize will_return para passar os valores de teste. Lembre que a ordem e a quantidade que sao passados importam.

        Depois de passar os parametros, chame a funcao production_code e verifique o valor de retorna com 
        assert_int_equal(ret, EXIT_SUCCEESS) ou assert_int_equal(ret, EXIT_FAILURE)
    */                                              

}

int main(void)
{
    const struct CMUnitTest tests[] = {
    cmocka_unit_test(test_successful_deposit),
    cmocka_unit_test(test_failed_deposit),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
