#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

void test_addition(void)
{
  CU_ASSERT(2 + 2 == 4);
  CU_ASSERT_EQUAL(3 + 3, 6);
}

void test_subtraction(void)
{
  CU_ASSERT(2 - 1 == 1);
  CU_ASSERT_EQUAL(2 - 2, -1); // Test failure
}

int main()
{
  CU_initialize_registry();

  CU_pSuite suite = CU_add_suite("List Test Suite", NULL, NULL);
  if (suite == NULL)
  {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (
      (CU_add_test(suite, "Test addition", test_addition) == NULL) ||
      (CU_add_test(suite, "Test subtraction", test_subtraction) == NULL))
  {
    CU_cleanup_registry();
    return CU_get_error();
  }

  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();

  CU_cleanup_registry();
  return CU_get_error();
}
