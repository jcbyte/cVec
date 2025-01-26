#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <CUnit/Automated.h>
#include <unistd.h>
#include "../include/list.h"
#include <errno.h>

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
  CU_ASSERT_EQUAL(errno, EINVAL);
  assert_size(l, 0);
  errno = 0;

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
  CU_ASSERT_EQUAL(errno, EINVAL);
  assert_size(l, 4);
  errno = 0;

  // Test inserting list at negative position
  lst_insert(&l, 99, -1);
  CU_ASSERT_EQUAL(errno, EINVAL);
  assert_size(l, 4);
  errno = 0;

  lst_destroy(&l);
}

void test_pop_front(void)
{
  // Test removing with 1 element
  List l = lst_create((int[]){1}, 1);
  CU_ASSERT_EQUAL(lst_pop_front(&l), 1);
  assert_size(l, 0);

  // Test removing with 0 elements
  CU_ASSERT_EQUAL(lst_pop_front(&l), -1);
  CU_ASSERT_EQUAL(errno, EINVAL);
  assert_size(l, 0);
  lst_destroy(&l);
  errno = 0;

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
  CU_ASSERT_EQUAL(lst_pop_back(&l), -1);
  CU_ASSERT_EQUAL(errno, EINVAL);
  assert_size(l, 0);
  lst_destroy(&l);
  errno = 0;

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
  CU_ASSERT_FALSE(lst_remove(&l, 2));
  assert_size(l, 1);

  // Test removing with 1 element
  CU_ASSERT_TRUE(lst_remove(&l, 1));
  assert_size(l, 0);

  // Test removing with 0 elements
  CU_ASSERT_FALSE(lst_remove(&l, 2));
  assert_size(l, 0);
  lst_destroy(&l);

  // Test removing unknown with multiple elements
  l = lst_create((int[]){1, 2, 3, 3, 4}, 5);
  CU_ASSERT_FALSE(lst_remove(&l, 10));
  assert_size(l, 5);
  assert_list_values(l, (int[]){1, 2, 3, 3, 4}, 5);

  // Test removing value where multiple exist
  CU_ASSERT_TRUE(lst_remove(&l, 3));
  assert_size(l, 4);
  assert_list_values(l, (int[]){1, 2, 3, 4}, 4);

  // Expected test
  CU_ASSERT_TRUE(lst_remove(&l, 2));
  assert_size(l, 3);
  assert_list_values(l, (int[]){1, 3, 4}, 3);

  lst_destroy(&l);
}

void test_remove_at(void)
{
  // Test removing with 1 element
  List l = lst_create((int[]){1}, 1);
  CU_ASSERT_EQUAL(lst_remove_at(&l, 0), 1);
  assert_size(l, 0);

  // Test removing with 0 elements
  CU_ASSERT_EQUAL(lst_remove_at(&l, 0), -1);
  CU_ASSERT_EQUAL(errno, EINVAL);
  assert_size(l, 0);
  lst_destroy(&l);
  errno = 0;

  // Test removing out of bounds
  l = lst_create((int[]){1, 2, 3}, 3);
  CU_ASSERT_EQUAL(lst_remove_at(&l, 99), -1);
  CU_ASSERT_EQUAL(errno, EINVAL);
  assert_size(l, 3);
  errno = 0;

  // Test removing at negative position
  CU_ASSERT_EQUAL(lst_remove_at(&l, -1), -1);
  CU_ASSERT_EQUAL(errno, EINVAL);
  assert_size(l, 3);
  errno = 0;

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
  CU_ASSERT_EQUAL(lst_at(l, 0), -1);
  CU_ASSERT_EQUAL(errno, EINVAL);
  lst_destroy(&l);
  errno = 0;

  // Test getting element out of bounds
  l = lst_create((int[]){1, 2, 3}, 3);
  CU_ASSERT_EQUAL(lst_at(l, 8), -1);
  CU_ASSERT_EQUAL(errno, EINVAL);
  errno = 0;

  // Test geting negative position
  CU_ASSERT_EQUAL(lst_at(l, -1), -1);
  CU_ASSERT_EQUAL(errno, EINVAL);
  errno = 0;

  // Expected test
  CU_ASSERT_EQUAL(lst_at(l, 0), 1);
  CU_ASSERT_EQUAL(lst_at(l, 1), 2);
  CU_ASSERT_EQUAL(lst_at(l, 2), 3);

  lst_destroy(&l);
}

void test_print(void)
{
  // Create a pipe
  int pipefd[2];
  if (pipe(pipefd) == -1)
  {
    CU_FAIL("Failed to create pipe.");
    return;
  }

  // Save original stdout file descriptor
  int original_stdout = dup(fileno(stdout));

  // Redirect stdout to the pipe
  dup2(pipefd[1], fileno(stdout));
  // Close write end of the pipe in the parent process
  close(pipefd[1]);

  // Test empty list
  List l = lst_create_empty();
  lst_print(l);
  // Ensure output is flushed to the pipe
  fflush(stdout);

  // Read from the pipe
  char buffer[20] = {0};
  read(pipefd[0], buffer, sizeof(buffer) - 1);

  CU_ASSERT_STRING_EQUAL(buffer, "[]");
  lst_destroy(&l);

  // Clear buffer
  memset(buffer, 0, sizeof(buffer));

  // Test a list with elements
  l = lst_create((int[]){1, 2, 3, 4}, 4);
  lst_print(l);
  // Ensure output is flushed to the pipe
  fflush(stdout);

  // Read from the pipe
  read(pipefd[0], buffer, sizeof(buffer) - 1);

  CU_ASSERT_STRING_EQUAL(buffer, "[1, 2, 3, 4]");
  lst_destroy(&l);

  // Close read end of the pipe
  close(pipefd[0]);

  // Restore the original stdout
  dup2(original_stdout, fileno(stdout));
  close(original_stdout);
}

void test_clear(void)
{
  // Test clearing empty list
  List l = lst_create_empty();
  lst_clear(&l);
  assert_size(l, 0);
  lst_destroy(&l);

  // Expected test
  l = lst_create((int[]){1, 2, 3, 4, 5}, 5);
  lst_clear(&l);
  assert_size(l, 0);
  lst_destroy(&l);
}

void test_front(void)
{
  // Test empty list
  List l = lst_create_empty();
  CU_ASSERT_EQUAL(lst_front(l), -1);
  CU_ASSERT_EQUAL(errno, EINVAL);
  lst_destroy(&l);
  errno = 0;

  // Test list with 1 element
  l = lst_create((int[]){2}, 1);
  CU_ASSERT_EQUAL(lst_front(l), 2);
  lst_destroy(&l);

  // Expected test
  l = lst_create((int[]){1, 2, 3, 4, 5}, 5);
  CU_ASSERT_EQUAL(lst_front(l), 1);
  lst_destroy(&l);
}

void test_end(void)
{
  // Test empty list
  List l = lst_create_empty();
  CU_ASSERT_EQUAL(lst_end(l), -1);
  CU_ASSERT_EQUAL(errno, EINVAL);
  lst_destroy(&l);
  errno = 0;

  // Test list with 1 element
  l = lst_create((int[]){2}, 1);
  CU_ASSERT_EQUAL(lst_end(l), 2);
  lst_destroy(&l);

  // Expected test
  l = lst_create((int[]){1, 2, 3, 4, 5}, 5);
  CU_ASSERT_EQUAL(lst_end(l), 5);
  lst_destroy(&l);
}

void test_size(void)
{
  // Expected tests
  List l = lst_create_empty();
  CU_ASSERT_EQUAL(lst_size(l), 0);
  lst_destroy(&l);

  l = lst_create((int[]){1}, 1);
  CU_ASSERT_EQUAL(lst_size(l), 1);
  lst_destroy(&l);

  l = lst_create((int[]){1, 2, 3, 4, 5}, 5);
  CU_ASSERT_EQUAL(lst_size(l), 5);
  lst_destroy(&l);
}

void test_empty(void)
{
  // Expected tests
  List l = lst_create_empty();
  CU_ASSERT_TRUE(lst_empty(l));
  lst_destroy(&l);

  l = lst_create((int[]){1}, 1);
  CU_ASSERT_FALSE(lst_empty(l));
  lst_destroy(&l);

  l = lst_create((int[]){1, 2, 3, 4, 5}, 5);
  CU_ASSERT_FALSE(lst_empty(l));
  lst_destroy(&l);
}

void test_swap(void)
{
  // Test empty list
  List l = lst_create_empty();
  lst_swap(&l, 0, 0);
  assert_size(l, 0);
  lst_destroy(&l);

  // Test list with 1 element
  l = lst_create((int[]){1}, 1);
  lst_swap(&l, 0, 0);
  assert_size(l, 1);
  assert_list_values(l, (int[]){1}, 1);
  lst_destroy(&l);

  // Test list with 2 elements
  l = lst_create((int[]){1, 2}, 2);
  lst_swap(&l, 1, 0);
  assert_size(l, 2);
  assert_list_values(l, (int[]){2, 1}, 2);
  lst_destroy(&l);

  // Test position 1 out of bounds
  l = lst_create((int[]){1, 2, 3, 4, 5}, 5);
  lst_swap(&l, 12, 1);
  CU_ASSERT_EQUAL(errno, EINVAL);
  assert_size(l, 5);
  assert_list_values(l, (int[]){1, 2, 3, 4, 5}, 5);
  errno = 0;

  // Test position 1 negative
  lst_swap(&l, -1, 1);
  CU_ASSERT_EQUAL(errno, EINVAL);
  assert_size(l, 5);
  assert_list_values(l, (int[]){1, 2, 3, 4, 5}, 5);
  errno = 0;

  // Test position 2 out of bounds
  lst_swap(&l, 2, 7);
  CU_ASSERT_EQUAL(errno, EINVAL);
  assert_size(l, 5);
  assert_list_values(l, (int[]){1, 2, 3, 4, 5}, 5);
  errno = 0;

  // Test position 2 negative
  lst_swap(&l, 3, -1);
  CU_ASSERT_EQUAL(errno, EINVAL);
  assert_size(l, 5);
  assert_list_values(l, (int[]){1, 2, 3, 4, 5}, 5);
  errno = 0;

  // Test both positions out of bounds
  lst_swap(&l, 12, 7);
  CU_ASSERT_EQUAL(errno, EINVAL);
  assert_size(l, 5);
  assert_list_values(l, (int[]){1, 2, 3, 4, 5}, 5);
  errno = 0;

  // Test both positions negative
  lst_swap(&l, -2, -1);
  CU_ASSERT_EQUAL(errno, EINVAL);
  assert_size(l, 5);
  assert_list_values(l, (int[]){1, 2, 3, 4, 5}, 5);
  errno = 0;

  // Test same position
  lst_swap(&l, 2, 2);
  assert_size(l, 5);
  assert_list_values(l, (int[]){1, 2, 3, 4, 5}, 5);

  // Test end to end
  lst_swap(&l, 0, 4);
  assert_size(l, 5);
  assert_list_values(l, (int[]){5, 2, 3, 4, 1}, 5);

  // Test adjacent elements at the start
  lst_swap(&l, 0, 1);
  assert_size(l, 5);
  assert_list_values(l, (int[]){2, 5, 3, 4, 1}, 5);

  // Test adjacent elements at the end
  lst_swap(&l, 3, 4);
  assert_size(l, 5);
  assert_list_values(l, (int[]){2, 5, 3, 1, 4}, 5);

  // Expected tests
  lst_swap(&l, 0, 2);
  assert_size(l, 5);
  assert_list_values(l, (int[]){3, 5, 2, 1, 4}, 5);

  lst_swap(&l, 3, 1);
  assert_size(l, 5);
  assert_list_values(l, (int[]){3, 1, 2, 5, 4}, 5);

  lst_destroy(&l);
}

int main(int argc, char *argv[])
{
  CU_initialize_registry();

  // Create test suites
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
      (CU_add_test(suite_remove, "Test remove_at", test_remove_at) == NULL) ||
      (CU_add_test(suite_util, "Test at", test_at) == NULL) ||
      (CU_add_test(suite_util, "Test print", test_print) == NULL) ||
      (CU_add_test(suite_util, "Test clear", test_clear) == NULL) ||
      (CU_add_test(suite_util, "Test front", test_front) == NULL) ||
      (CU_add_test(suite_util, "Test end", test_end) == NULL) ||
      (CU_add_test(suite_util, "Test size", test_size) == NULL) ||
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
