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
    // Always ensure input parameters are what're expected
    check_expected(money);
    check_expected_ptr(bank);

    // We can define as many mock_types as we want.
    bool is_valid_account = mock_type(bool);
    if (!is_valid_account) { return EXIT_FAILURE; }

    int minimum_money = mock_type(int);
    if (minimum_money <= 100) { return EXIT_FAILURE; }

    char* bank_name = mock_ptr_type(char*);
    if (strcmp(bank_name, "WEG") == 0) { return EXIT_FAILURE; }


    return EXIT_SUCCESS;
}

