#include "munit/munit.h"
#include "snekobject.h"
#include "tests/refcount.h"
#include "tests/sneklang.h"

int main() {

  MunitTest refcount_tests[] = {
      {
          "/int",
          test_int_has_refcount,
          NULL,
          NULL,
          MUNIT_TEST_OPTION_NONE,
          NULL,
      },
      {
          "/float",
          test_float_has_refcount,
          NULL,
          NULL,
          MUNIT_TEST_OPTION_NONE,
          NULL,
      },
      {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  };

  MunitTest lang_tests[] = {
      {
          "/integer/positive",
          test_integer_positive,
          NULL,
          NULL,
          MUNIT_TEST_OPTION_NONE,
          NULL,
      },
      {
          "/integer/zero",
          test_integer_zero,
          NULL,
          NULL,
          MUNIT_TEST_OPTION_NONE,
          NULL,
      },
      {
          "/integer/negative",
          test_integer_negative,
          NULL,
          NULL,
          MUNIT_TEST_OPTION_NONE,
          NULL,
      },
      {
          "/float/positive",
          test_float_positive,
          NULL,
          NULL,
          MUNIT_TEST_OPTION_NONE,
          NULL,
      },
      {
          "/float/zero",
          test_float_zero,
          NULL,
          NULL,
          MUNIT_TEST_OPTION_NONE,
          NULL,
      },
      {
          "/float/negative",
          test_float_negative,
          NULL,
          NULL,
          MUNIT_TEST_OPTION_NONE,
          NULL,
      },
      {
          "/string/copies",
          test_string_copied,
          NULL,
          NULL,
          MUNIT_TEST_OPTION_NONE,
          NULL,
      },
      {
          "/vector3/null",
          test_vector3_null,
          NULL,
          NULL,
          MUNIT_TEST_OPTION_NONE,
          NULL,
      },
      {
          "/vector3/multiple-objects",
          test_vector3_multiple_objects,
          NULL,
          NULL,
          MUNIT_TEST_OPTION_NONE,
          NULL,
      },
      {
          "/vector3/same-object",
          test_vector3_same_object,
          NULL,
          NULL,
          MUNIT_TEST_OPTION_NONE,
          NULL,
      },
      {
          "/array/empty",
          test_create_empty_array,
          NULL,
          NULL,
          MUNIT_TEST_OPTION_NONE,
          NULL,
      },
      {
          "/array/calloc",
          test_array_used_calloc,
          NULL,
          NULL,
          MUNIT_TEST_OPTION_NONE,
          NULL,
      },
      {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  };

  MunitSuite tests[] = {
      {
          "/sneklang",
          lang_tests,
          NULL,
          1,
          MUNIT_SUITE_OPTION_NONE,
      },
      {
          "/refcount",
          refcount_tests,
          NULL,
          1,
          MUNIT_SUITE_OPTION_NONE,
      },
      {NULL, NULL, NULL, 0, MUNIT_SUITE_OPTION_NONE},
  };

  MunitSuite suites = {
      "", NULL, tests, 1, MUNIT_SUITE_OPTION_NONE,
  };

  return munit_suite_main(&suites, NULL, 0, NULL);
}
