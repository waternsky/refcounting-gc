#include "../munit/munit.h"
#include "../snekobject.h"

MunitResult test_vector3_refcounting_same() {
  snek_object_t *obj = new_snek_integer(1);

  snek_object_t *vec = new_snek_vector3(obj, obj, obj);
  munit_assert_int(obj->refcount, ==, 4);
  refcount_dec(obj);
  munit_assert_int(obj->data.v_int, ==, 1);
  refcount_dec(vec);
  munit_assert_int(obj->refcount, ==, 0);
  return MUNIT_OK;
}

MunitResult test_vector3_refcounting() {
  snek_object_t *obj1 = new_snek_integer(1);
  snek_object_t *obj2 = new_snek_integer(2);
  snek_object_t *obj3 = new_snek_integer(3);

  snek_object_t *vec = new_snek_vector3(obj1, obj2, obj3);

  munit_assert_int(obj1->refcount, ==, 2);
  munit_assert_int(obj2->refcount, ==, 2);
  munit_assert_int(obj3->refcount, ==, 2);

  refcount_dec(obj1);

  munit_assert_int(obj1->data.v_int, ==, 1);
  refcount_dec(vec);
  munit_assert_int(obj1->refcount, ==, 0);
  munit_assert_int(obj2->data.v_int, ==, 2);
  munit_assert_int(obj3->data.v_int, ==, 3);

  refcount_dec(obj2);
  refcount_dec(obj3);
  return MUNIT_OK;
}

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

MunitResult test_inc_refcount() {
  snek_object_t *obj = new_snek_integer(42);
  munit_assert_int(obj->refcount, ==, 1);
  refcount_inc(obj);
  refcount_inc(obj);
  refcount_inc(obj);
  refcount_inc(obj);
  munit_assert_int(obj->refcount, ==, 5);
  free(obj);
  return MUNIT_OK;
}

MunitResult test_dec_refcount() {
  snek_object_t *obj = new_snek_float(2.0);
  refcount_inc(obj);
  munit_assert_int(obj->refcount, ==, 2);
  refcount_dec(obj);
  munit_assert_int(obj->refcount, ==, 1);
  free(obj);
  return MUNIT_OK;
}

MunitResult test_free_refcount() {
  snek_object_t *obj = new_snek_float(3.0);
  refcount_inc(obj);
  munit_assert_int(obj->refcount, ==, 2);
  refcount_dec(obj);
  munit_assert_int(obj->refcount, ==, 1);
  refcount_dec(obj);
  munit_assert_int(obj->refcount, ==, 0);
  return MUNIT_OK;
}
