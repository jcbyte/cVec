#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../list/list.h"

void test_create(void)
{
  List l = lst_create();

  CU_ASSERT_EQUAL(lst_size(l), 0);
}

void test_push_front(void)
{
  List l = lst_create();

  lst_push_front(&l, 2);
  CU_ASSERT_EQUAL(lst_size(l), 1);
  CU_ASSERT_EQUAL(lst_at(l, 0), 2);

  lst_push_front(&l, 1);
  CU_ASSERT_EQUAL(lst_size(l), 2);
  CU_ASSERT_EQUAL(lst_at(l, 0), 1);
  CU_ASSERT_EQUAL(lst_at(l, 1), 2);
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
      (CU_add_test(suite, "Test create", test_create) == NULL) ||
      (CU_add_test(suite, "Test push_front", test_push_front) == NULL))
  {
    CU_cleanup_registry();
    return CU_get_error();
  }

  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();

  CU_cleanup_registry();
  return CU_get_error();
}
