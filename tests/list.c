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

void test_create_empty(void)
{
  // Expected test
  List l = lst_create_empty();
  assert_size(l, 0);
  lst_destroy(&l);
}

void test_create(void)
{
  // Expected tests
  List l = lst_create((int[]){}, 0);
  assert_size(l, 0);
  lst_destroy(&l);

  l = lst_create((int[]){42}, 1);
  assert_size(l, 1);
  assert_list_values(l, (int[]){42}, 1);
  lst_destroy(&l);

  l = lst_create((int[]){1, 2, 3, 4, 5, 6}, 6);
  assert_size(l, 6);
  assert_list_values(l, (int[]){1, 2, 3, 4, 5, 6}, 6);
  lst_destroy(&l);
}

void test_push_front(void)
{
  // Expected tests
  List l = lst_create_empty();

  lst_push_front(&l, 2);
  assert_size(l, 1);
  assert_list_values(l, (int[]){2}, 1);

  lst_push_front(&l, 1);
  assert_size(l, 2);
  assert_list_values(l, (int[]){1, 2}, 2);

  lst_destroy(&l);
}

void test_push_back(void)
{
  // Expected tests
  List l = lst_create_empty();

  lst_push_back(&l, 1);
  assert_size(l, 1);
  assert_list_values(l, (int[]){1}, 1);

  lst_push_back(&l, 2);
  assert_size(l, 2);
  assert_list_values(l, (int[]){1, 2}, 2);

  lst_destroy(&l);
}

void test_insert(void)
{
  List l = lst_create_empty();

  // Test inserting list out of bounds with empty list
  lst_insert(&l, 99, 7);
  assert_size(l, 0);

  // Expected tests
  lst_insert(&l, 3, 0);
  assert_size(l, 1);
  assert_list_values(l, (int[]){3}, 1);

  lst_insert(&l, 1, 0);
  assert_size(l, 2);
  assert_list_values(l, (int[]){1, 3}, 2);

  lst_insert(&l, 2, 1);
  assert_size(l, 3);
  assert_list_values(l, (int[]){1, 2, 3}, 3);

  lst_insert(&l, 4, 3);
  assert_size(l, 4);
  assert_list_values(l, (int[]){1, 2, 3, 4}, 4);

  // Test inserting list out of bounds with filled list
  lst_insert(&l, 99, 5);
  assert_size(l, 4);

  // Test inserting list at negative position
  lst_insert(&l, 99, -1);
  assert_size(l, 4);

  lst_destroy(&l);
}

void test_pop_front(void)
{
  // Test removing with 1 element
  List l = lst_create((int[]){1}, 1);
  CU_ASSERT_EQUAL(lst_pop_front(&l), 1);
  assert_size(l, 0);

  // Test removing with 0 elements
  CU_ASSERT_EQUAL(lst_pop_front(&l), NULL);
  assert_size(l, 0);
  lst_destroy(&l);

  // Expected test
  l = lst_create((int[]){1, 2, 3}, 3);
  CU_ASSERT_EQUAL(lst_pop_front(&l), 1);
  assert_size(l, 2);
  assert_list_values(l, (int[]){2, 3}, 2);
  lst_destroy(&l);
}

void test_pop_back(void)
{
  // Test removing with 1 element
  List l = lst_create((int[]){1}, 1);
  CU_ASSERT_EQUAL(lst_pop_back(&l), 1);
  assert_size(l, 0);

  // Test removing with 0 elements
  CU_ASSERT_EQUAL(lst_pop_back(&l), NULL);
  assert_size(l, 0);
  lst_destroy(&l);

  // Expected test
  l = lst_create((int[]){1, 2, 3}, 3);
  CU_ASSERT_EQUAL(lst_pop_back(&l), 3);
  assert_size(l, 2);
  assert_list_values(l, (int[]){1, 2}, 2);
  lst_destroy(&l);
}

void test_remove(void)
{
  // Test removing unknown with 1 element
  List l = lst_create((int[]){1}, 1);
  CU_ASSERT_EQUAL(lst_remove(&l, 2), NULL);
  assert_size(l, 1);

  // Test removing with 1 element
  CU_ASSERT_EQUAL(lst_remove(&l, 1), 1);
  assert_size(l, 0);

  // Test removing with 0 elements
  CU_ASSERT_EQUAL(lst_remove(&l, 2), NULL);
  assert_size(l, 0);
  lst_destroy(&l);

  // Test removing unknown with multiple elements
  l = lst_create((int[]){1, 2, 3, 3, 4}, 5);
  CU_ASSERT_EQUAL(lst_remove(&l, 10), NULL);
  assert_size(l, 5);
  assert_list_values(l, (int[]){1, 2, 3, 3, 4}, 5);

  // Test removing value where multiple exist
  CU_ASSERT_EQUAL(lst_remove(&l, 3), 3);
  assert_size(l, 4);
  assert_list_values(l, (int[]){1, 2, 3, 4}, 4);

  // Expected test
  CU_ASSERT_EQUAL(lst_remove(&l, 2), 2);
  assert_size(l, 3);
  assert_list_values(l, (int[]){1, 3, 4}, 4);
}

void test_remove_at(void)
{
  // Test removing with 1 element
  List l = lst_create((int[]){1}, 1);
  CU_ASSERT_EQUAL(lst_remove_at(&l, 0), 1);
  assert_size(l, 0);

  // Test removing with 0 elements
  CU_ASSERT_EQUAL(lst_remove_at(&l, 0), NULL);
  assert_size(l, 0);
  lst_destroy(&l);

  // Expected test
  l = lst_create((int[]){1, 2, 3}, 3);
  CU_ASSERT_EQUAL(lst_remove_at(&l, 7), NULL);
  assert_size(l, 3);
  assert_list_values(l, (int[]){1, 2, 3}, 3);

  // Expected test
  CU_ASSERT_EQUAL(lst_remove_at(&l, 1), 2);
  assert_size(l, 2);
  assert_list_values(l, (int[]){1, 3}, 2);

  // Test removing at end
  CU_ASSERT_EQUAL(lst_remove_at(&l, 1), 3);
  assert_size(l, 1);
  assert_list_values(l, (int[]){1}, 1);

  lst_destroy(&l);
}

void test_at(void)
{
  // Test getting element from empty list
  List l = lst_create_empty();
  CU_ASSERT_EQUAL(lst_at(l, 0), NULL);
  lst_destroy(&l);

  // Test getting element out of bounds
  l = lst_create((int[]){1, 2, 3}, 3);
  CU_ASSERT_EQUAL(lst_at(l, 8), NULL);

  // Test geting negative position
  CU_ASSERT_EQUAL(lst_at(l, -1), NULL);

  // Expected test
  // These are done using internal structure as our helper functions use lst_at
  _Node *a = l._start->next;
  _Node *b = a->next;
  _Node *c = b->next;
  CU_ASSERT_EQUAL(lst_at(l, 0), a->data);
  CU_ASSERT_EQUAL(lst_at(l, 1), b->data);
  CU_ASSERT_EQUAL(lst_at(l, 2), c->data);
}

void test_print(void);
void tst_clear(void);
void test_front(void);
void test_end(void);
void test_size(void)
{
  // These are done using internal structure as our helper functions use lst_at
}
void test_empty(void);
void test_swap(void);

int main()
{
  CU_initialize_registry();

  CU_pSuite suite_create = CU_add_suite("List Creation Test Suite", NULL, NULL);
  CU_pSuite suite_insert = CU_add_suite("List Insertion Test Suite", NULL, NULL);
  CU_pSuite suite_remove = CU_add_suite("List Removal Test Suite", NULL, NULL);
  CU_pSuite suite_util = CU_add_suite("List Util Test Suite", NULL, NULL);
  if (
      (suite_create == NULL) ||
      (suite_insert == NULL) ||
      (suite_remove == NULL) ||
      (suite_util == NULL))
  {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (
      (CU_add_test(suite_create, "Test create_empty", test_create_empty) == NULL) ||
      (CU_add_test(suite_create, "Test create", test_create) == NULL) ||
      (CU_add_test(suite_insert, "Test push_front", test_push_front) == NULL) ||
      (CU_add_test(suite_insert, "Test push_back", test_push_back) == NULL) ||
      (CU_add_test(suite_insert, "Test insert", test_insert) == NULL) ||
      (CU_add_test(suite_remove, "Test pop_front", test_insert) == NULL) ||
      (CU_add_test(suite_remove, "Test pop_back", test_insert) == NULL) ||
      (CU_add_test(suite_remove, "Test remove", test_insert) == NULL) ||
      (CU_add_test(suite_remove, "Test remove_at", test_insert) == NULL) ||
      (CU_add_test(suite_util, "Test at", test_insert) == NULL) ||
      (CU_add_test(suite_util, "Test print", test_insert) == NULL) ||
      (CU_add_test(suite_util, "Test clear", test_insert) == NULL) ||
      (CU_add_test(suite_util, "Test front", test_insert) == NULL) ||
      (CU_add_test(suite_util, "Test end", test_insert) == NULL) ||
      (CU_add_test(suite_util, "Test size", test_insert) == NULL) ||
      (CU_add_test(suite_util, "Test empty", test_insert) == NULL) ||
      (CU_add_test(suite_util, "Test swap", test_insert) == NULL))
  {
    CU_cleanup_registry();
    return CU_get_error();
  }

  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();

  CU_cleanup_registry();
  return CU_get_error();
}
