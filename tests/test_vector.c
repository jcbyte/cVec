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

  // Test inserting out of bounds with empty vector
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

  // Test inserting out of bounds with filled vector
  vec_insert(&v, 99, 5);
  CU_ASSERT_EQUAL(errno, EINVAL);
  assert_size(v, 4);
  errno = 0;

  // Test inserting at negative position
  vec_insert(&v, 99, -1);
  CU_ASSERT_EQUAL(errno, EINVAL);
  assert_size(v, 4);
  errno = 0;

  vec_destroy(&v);
}


void test_pop_front(void)
{
  // Test removing with 1 element
  Vector v = vec_create((int[]){1}, 1);
  CU_ASSERT_EQUAL(vec_pop_front(&v), 1);
  assert_size(v, 0);

  // Test removing with 0 elements
  CU_ASSERT_EQUAL(vec_pop_front(&v), -1);
  CU_ASSERT_EQUAL(errno, EINVAL);
  assert_size(v, 0);
  vec_destroy(&v);
  errno = 0;

  // Expected test
  v = vec_create((int[]){1, 2, 3}, 3);
  CU_ASSERT_EQUAL(vec_pop_front(&v), 1);
  assert_size(v, 2);
  assert_vector_values(v, (int[]){2, 3}, 2);
  vec_destroy(&v);
}

void test_pop_back(void)
{
  // Test removing with 1 element
  Vector v = vec_create((int[]){1}, 1);
  CU_ASSERT_EQUAL(vec_pop_back(&v), 1);
  assert_size(v, 0);

  // Test removing with 0 elements
  CU_ASSERT_EQUAL(vec_pop_back(&v), -1);
  CU_ASSERT_EQUAL(errno, EINVAL);
  assert_size(v, 0);
  vec_destroy(&v);
  errno = 0;

  // Expected test
  v = vec_create((int[]){1, 2, 3}, 3);
  CU_ASSERT_EQUAL(vec_pop_back(&v), 3);
  assert_size(v, 2);
  assert_vector_values(v, (int[]){1, 2}, 2);
  vec_destroy(&v);
}

void test_remove(void)
{
  // Test removing unknown with 1 element
  Vector v = vec_create((int[]){1}, 1);
  CU_ASSERT_FALSE(vec_remove(&v, 2));
  assert_size(v, 1);

  // Test removing with 1 element
  CU_ASSERT_TRUE(vec_remove(&v, 1));
  assert_size(v, 0);

  // Test removing with 0 elements
  CU_ASSERT_FALSE(vec_remove(&v, 2));
  assert_size(v, 0);
  vec_destroy(&v);

  // Test removing unknown with multiple elements
  v = vec_create((int[]){1, 2, 3, 3, 4}, 5);
  CU_ASSERT_FALSE(vec_remove(&v, 10));
  assert_size(v, 5);
  assert_vector_values(v, (int[]){1, 2, 3, 3, 4}, 5);

  // Test removing value where multiple exist
  CU_ASSERT_TRUE(vec_remove(&v, 3));
  assert_size(v, 4);
  assert_vector_values(v, (int[]){1, 2, 3, 4}, 4);

  // Expected test
  CU_ASSERT_TRUE(vec_remove(&v, 2));
  assert_size(v, 3);
  assert_vector_values(v, (int[]){1, 3, 4}, 3);

  vec_destroy(&v);
}

void test_remove_at(void)
{
  // Test removing with 1 element
  Vector v = vec_create((int[]){1}, 1);
  CU_ASSERT_EQUAL(vec_remove_at(&v, 0), 1);
  assert_size(v, 0);

  // Test removing with 0 elements
  CU_ASSERT_EQUAL(vec_remove_at(&v, 0), -1);
  CU_ASSERT_EQUAL(errno, EINVAL);
  assert_size(v, 0);
  vec_destroy(&v);
  errno = 0;

  // Test removing out of bounds
  v = vec_create((int[]){1, 2, 3}, 3);
  CU_ASSERT_EQUAL(vec_remove_at(&v, 99), -1);
  CU_ASSERT_EQUAL(errno, EINVAL);
  assert_size(v, 3);
  errno = 0;

  // Test removing at negative position
  CU_ASSERT_EQUAL(vec_remove_at(&v, -1), -1);
  CU_ASSERT_EQUAL(errno, EINVAL);
  assert_size(v, 3);
  errno = 0;

  // Expected test
  CU_ASSERT_EQUAL(vec_remove_at(&v, 1), 2);
  assert_size(v, 2);
  assert_vector_values(v, (int[]){1, 3}, 2);

  // Test removing at end
  CU_ASSERT_EQUAL(vec_remove_at(&v, 1), 3);
  assert_size(v, 1);
  assert_vector_values(v, (int[]){1}, 1);

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
      (CU_add_test(suite_insert, "Test insert", test_insert) == NULL) ||
      (CU_add_test(suite_remove, "Test pop_front", test_pop_front) == NULL) ||
      (CU_add_test(suite_remove, "Test pop_back", test_pop_back) == NULL) ||
      (CU_add_test(suite_remove, "Test remove", test_remove) == NULL) ||
      (CU_add_test(suite_remove, "Test remove_at", test_remove_at) == NULL)|
      (CU_add_test(suite_util, "Test at", test_at) == NULL) ||
      (CU_add_test(suite_util, "Test print", test_print) == NULL) ||
      (CU_add_test(suite_util, "Test clear", test_clear) == NULL) ||
      (CU_add_test(suite_util, "Test front", test_front) == NULL) ||
      (CU_add_test(suite_util, "Test end", test_end) == NULL) ||
      (CU_add_test(suite_util, "Test size", test_size) == NULL) ||
      // (CU_add_test(suite_util, "Test capacity", test_capacity) == NULL) ||
      // (CU_add_test(suite_util, "Test shrink_to_fit", test_shrink_to_fit) == NULL) ||
      (CU_add_test(suite_util, "Test empty", test_empty) == NULL) ||
      (CU_add_test(suite_util, "Test swap", test_swap) == NULL))
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
