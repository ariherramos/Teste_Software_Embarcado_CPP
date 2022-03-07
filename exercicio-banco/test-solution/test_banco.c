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
      int deposit_money = 200;
      const char* deposit_bank = "Citibank";
     
      // These expects must match the order of declaration of "check_expected"
      // in __wrap_deposit()
      expect_value(__wrap_deposit, money, deposit_money);
      expect_string(__wrap_deposit, bank, deposit_bank);

      // These will_return's must match the order of declaration of "mock_type"s
      // in __wrap_deposit()
      will_return(__wrap_deposit, true);  // assume account is valid
      will_return(__wrap_deposit, deposit_money);
      will_return(__wrap_deposit, deposit_bank);

      // Test the production code
      int ret = production_code(deposit_money, deposit_bank);

      assert_int_equal(ret, EXIT_SUCCESS);
}

static void test_failed_deposit(void** state)
{
      (void)state;  //unused variable                                                      

      // These expects must match the order of declaration of "check_expected"  in __wrap_deposit()
                                                                                                                                                                          
      int deposit_money = 200;
      const char* deposit_bank = "Citibank";
      
      expect_value(__wrap_deposit, money, deposit_money);
      expect_string(__wrap_deposit, bank, deposit_bank);

      // These will_return's must match the order of declaration of "mock_type"s                                                                                                      
      // in __wrap_deposit()                                                                                                                                        
      will_return(__wrap_deposit, false);  // assume account is invalid
      // Test the production code                                                               
      int ret = production_code(deposit_money, deposit_bank);

      assert_int_equal(ret, EXIT_FAILURE);
}

int main(void)
{
      const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_successful_deposit),
        cmocka_unit_test(test_failed_deposit),
      };

      return cmocka_run_group_tests(tests, NULL, NULL);
}
