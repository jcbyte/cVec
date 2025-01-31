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

void test_sanity(void)
{
  // Expected tests
  CU_ASSERT_TRUE(1);
}

int main(int argc, char *argv[])
{
  CU_initialize_registry();

  // Create test suites
  CU_pSuite suite = CU_add_suite("Vector Test Suite", NULL, NULL);
  if (
      (suite == NULL))
  {
    CU_cleanup_registry();
    return CU_get_error();
  }

  // Add tests to suites
  if (
      (CU_add_test(suite, "Test sanity", test_sanity) == NULL))
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
