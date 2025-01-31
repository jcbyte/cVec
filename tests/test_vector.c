#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <CUnit/Automated.h>
#include <unistd.h>
#include "../include/vector.h"
#include <errno.h>

void assert_size(Vector vec, size_t expected_size)
{
  CU_ASSERT_EQUAL(vec_size(vec), expected_size);
}

void assert_at(Vector vec, size_t position, int expected_value)
{
  CU_ASSERT_EQUAL(vec_at(vec, position), expected_value);
}

void assert_vector_values(Vector vec, int *expected_values, size_t length)
{
  for (size_t i = 0; i < length; i++)
  {
    assert_at(vec, i, expected_values[i]);
  }
}

void test_create_empty(void)
{
  // Expected test
  Vector v = vec_create_empty();
  assert_size(v, 0);
  vec_destroy(&v);
}

void test_create(void)
{
  // Expected tests
  Vector v = vec_create((int[]){}, 0);
  assert_size(v, 0);
  vec_destroy(&v);

  v = vec_create((int[]){42}, 1);
  assert_size(v, 1);
  assert_vector_values(v, (int[]){42}, 1);
  vec_destroy(&v);

  v = vec_create((int[]){1, 2, 3, 4, 5, 6}, 6);
  assert_size(v, 6);
  assert_vector_values(v, (int[]){1, 2, 3, 4, 5, 6}, 6);
  vec_destroy(&v);
}


void test_push_front(void)
{
  // Expected tests
  Vector v = vec_create_empty();

  vec_push_front(&v, 2);
  assert_size(v, 1);
  assert_vector_values(v, (int[]){2}, 1);

  vec_push_front(&v, 1);
  assert_size(v, 2);
  assert_vector_values(v, (int[]){1, 2}, 2);

  vec_destroy(&v);
}

void test_push_back(void)
{
  // Expected tests
  Vector v = vec_create_empty();

  vec_push_back(&v, 1);
  assert_size(v, 1);
  assert_vector_values(v, (int[]){1}, 1);

  vec_push_back(&v, 2);
  assert_size(v, 2);
  assert_vector_values(v, (int[]){1, 2}, 2);

  vec_destroy(&v);
}

void test_insert(void)
{
  Vector v = vec_create_empty();

  // Test inserting list out of bounds with empty list
  vec_insert(&v, 99, 7);
  CU_ASSERT_EQUAL(errno, EINVAL);
  assert_size(v, 0);
  errno = 0;

  // Expected tests
  vec_insert(&v, 3, 0);
  assert_size(v, 1);
  assert_vector_values(v, (int[]){3}, 1);

  vec_insert(&v, 1, 0);
  assert_size(v, 2);
  assert_vector_values(v, (int[]){1, 3}, 2);

  vec_insert(&v, 2, 1);
  assert_size(v, 3);
  assert_vector_values(v, (int[]){1, 2, 3}, 3);

  vec_insert(&v, 4, 3);
  assert_size(v, 4);
  assert_vector_values(v, (int[]){1, 2, 3, 4}, 4);

  // Test inserting list out of bounds with filled list
  vec_insert(&v, 99, 5);
  CU_ASSERT_EQUAL(errno, EINVAL);
  assert_size(v, 4);
  errno = 0;

  // Test inserting list at negative position
  vec_insert(&v, 99, -1);
  CU_ASSERT_EQUAL(errno, EINVAL);
  assert_size(v, 4);
  errno = 0;

  vec_destroy(&v);
}

int main(int argc, char *argv[])
{
  CU_initialize_registry();

  // Create test suites
  CU_pSuite suite_create = CU_add_suite("Vector Creation Test Suite", NULL, NULL);
  CU_pSuite suite_insert = CU_add_suite("Vector Insertion Test Suite", NULL, NULL);
  CU_pSuite suite_remove = CU_add_suite("Vector Removal Test Suite", NULL, NULL);
  CU_pSuite suite_util = CU_add_suite("Vector Util Test Suite", NULL, NULL);
  if (
      (suite_create == NULL) ||
      (suite_insert == NULL) ||
      (suite_remove == NULL) ||
      (suite_util == NULL))
  {
    CU_cleanup_registry();
    return CU_get_error();
  }

  // Add tests to suites
  if (
      (CU_add_test(suite_create, "Test create_empty", test_create_empty) == NULL) ||
      (CU_add_test(suite_create, "Test create", test_create) == NULL) ||
      (CU_add_test(suite_insert, "Test push_front", test_push_front) == NULL) ||
      (CU_add_test(suite_insert, "Test push_back", test_push_back) == NULL) ||
      (CU_add_test(suite_insert, "Test insert", test_insert) == NULL))// ||
      // (CU_add_test(suite_remove, "Test pop_front", test_pop_front) == NULL) ||
      // (CU_add_test(suite_remove, "Test pop_back", test_pop_back) == NULL) ||
      // (CU_add_test(suite_remove, "Test remove", test_remove) == NULL) ||
      // (CU_add_test(suite_remove, "Test remove_at", test_remove_at) == NULL) ||
      // (CU_add_test(suite_util, "Test at", test_at) == NULL) ||
      // (CU_add_test(suite_util, "Test print", test_print) == NULL) ||
      // (CU_add_test(suite_util, "Test clear", test_clear) == NULL) ||
      // (CU_add_test(suite_util, "Test front", test_front) == NULL) ||
      // (CU_add_test(suite_util, "Test end", test_end) == NULL) ||
      // (CU_add_test(suite_util, "Test size", test_size) == NULL) ||
      // (CU_add_test(suite_util, "Test empty", test_empty) == NULL) ||
      // (CU_add_test(suite_util, "Test swap", test_swap) == NULL))
  {
    CU_cleanup_registry();
    return CU_get_error();
  }

  // Run test
  if (argc <= 1)
  {
    // Print output to console
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
  }
  else
  {
    // Log result as given file (this will be appended with "-Results.xml")
    CU_set_output_filename(argv[1]);
    // CU_list_tests_to_file();
    CU_automated_run_tests();
  }

  int failures = CU_get_number_of_tests_failed();
  CU_cleanup_registry();

  return failures > 0 ? 1 : 0;
}
