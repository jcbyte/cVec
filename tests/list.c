#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../list/list.h"

void assert_size(List lst, size_t expected_size)
{
  CU_ASSERT_EQUAL(lst_size(lst), expected_size);
}

void assert_at(List l, size_t position, int expected_value)
{
  CU_ASSERT_EQUAL(lst_at(l, position), expected_value);
}

void assert_list_values(List l, int *expected_values, size_t length)
{
  for (size_t i = 0; i < length; i++)
  {
    assert_at(l, i, expected_values[i]);
  }
}

void test_create(void)
{
  List l = lst_create();

  assert_size(l, 0);
}

void test_push_front(void)
{
  List l = lst_create();

  lst_push_front(&l, 2);
  assert_size(l, 1);
  assert_list_values(l, (int[]){2}, 1);

  lst_push_front(&l, 1);
  assert_size(l, 2);
  assert_list_values(l, (int[]){1, 2}, 2);
}

void test_push_back(void)
{
  List l = lst_create();

  lst_push_back(&l, 1);
  assert_size(l, 1);
  assert_list_values(l, (int[]){1}, 1);

  lst_push_back(&l, 2);
  assert_size(l, 2);
  assert_list_values(l, (int[]){1, 2}, 2);
}

void test_insert(void)
{
  List l = lst_create();

  lst_insert(&l, 3, 0);
  assert_size(l, 1);
  assert_list_values(l, (int[]){3}, 1);

  lst_insert(&l, 99, 3);
  assert_size(l, 1);

  lst_insert(&l, 1, 0);
  assert_size(l, 2);
  assert_list_values(l, (int[]){1, 3}, 2);

  lst_insert(&l, 2, 1);
  assert_size(l, 3);
  assert_list_values(l, (int[]){1, 2, 3}, 3);

  lst_insert(&l, 4, 3);
  assert_size(l, 4);
  assert_list_values(l, (int[]){1, 2, 3, 4}, 4);
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
      (CU_add_test(suite, "Test push_front", test_push_front) == NULL) ||
      (CU_add_test(suite, "Test push_back", test_push_back) == NULL) ||
      (CU_add_test(suite, "Test insert", test_insert) == NULL))
  {
    CU_cleanup_registry();
    return CU_get_error();
  }

  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();

  CU_cleanup_registry();
  return CU_get_error();
}
