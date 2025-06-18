#include "munit/munit.h"
#include "snekobject.h"

/* Language tests */

MunitResult test_create_empty_array() {
  snek_object_t *obj = new_snek_array(2);
  munit_assert_int(obj->kind, ==, ARRAY);
  munit_assert_ulong(obj->data.v_array.size, ==, 2);
  free(obj->data.v_array.elements);
  free(obj);
  return MUNIT_OK;
}

/* Refcount tests*/

MunitResult test_int_has_refcount() {
  snek_object_t *obj = new_snek_integer(10);
  munit_assert_int(obj->refcount, ==, 1);
  free(obj);
  return MUNIT_OK;
}

MunitResult test_float_has_refcount() {
  snek_object_t *obj = new_snek_float(1.5);
  munit_assert_int(obj->refcount, ==, 1);
  return MUNIT_OK;
}

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
          "/empty-array",
          test_create_empty_array,
          NULL,
          NULL,
          MUNIT_TEST_OPTION_NONE,
          NULL,
      },
      {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  };

  MunitSuite refcount[] = {
      {
          "/refcount",
          refcount_tests,
          NULL,
          1,
          MUNIT_SUITE_OPTION_NONE,
      },
      {
          "/sneklang",
          lang_tests,
          NULL,
          1,
          MUNIT_SUITE_OPTION_NONE,
      },
      {NULL, NULL, NULL, 0, MUNIT_SUITE_OPTION_NONE},
  };

  MunitSuite suites = {
      "/refcount-gc", NULL, refcount, 1, MUNIT_SUITE_OPTION_NONE,
  };

  return munit_suite_main(&suites, NULL, 0, NULL);
}
