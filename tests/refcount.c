#include "../munit/munit.h"
#include "../snekobject.h"

MunitResult test_int_has_refcount() {
  snek_object_t *obj = new_snek_integer(10);
  munit_assert_int(obj->refcount, ==, 1);
  free(obj);
  return MUNIT_OK;
}

MunitResult test_float_has_refcount() {
  snek_object_t *obj = new_snek_float(1.5);
  munit_assert_int(obj->refcount, ==, 1);
  free(obj);
  return MUNIT_OK;
}
