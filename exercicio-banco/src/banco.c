#include "banco.h"
#include "deposit.h"
#include <stdio.h>

/* Usar EXIT_FAILURE em caso de falha ou EXIT_SUCCESS em caso de sucesso */
int production_code(int money, const char* bank)
{
    int ret = EXIT_FAILURE;

    if (bank) {
        ret = deposit(money, bank);
    }

    return ret;
}

