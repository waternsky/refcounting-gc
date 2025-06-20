#include "refcount.h"
#include "../munit/munit.h"
#include "../snekobject.h"

MunitResult test_array_set() {
  snek_object_t *foo = new_snek_integer(1);
  snek_object_t *arr = new_snek_array(1);

  snek_array_set(arr, 0, foo);
  munit_assert_int(foo->refcount, ==, 2);
  munit_assert_ptr(snek_array_get(arr, 0), ==, foo);
  refcount_dec(foo);
  refcount_dec(arr);
  return MUNIT_OK;
}

MunitResult test_array_get() {
  snek_object_t *foo = new_snek_integer(22);
  snek_object_t *bar = new_snek_integer(12);
  snek_object_t *arr = new_snek_array(2);

  snek_array_set(arr, 0, foo);
  snek_array_set(arr, 1, bar);

  munit_assert_ptr(snek_array_get(arr, 0), ==, foo);
  munit_assert_ptr(snek_array_get(arr, 1), ==, bar);

  refcount_dec(foo);
  refcount_dec(bar);

  refcount_dec(arr);
  munit_assert_int(foo->refcount, ==, 0);
  munit_assert_int(bar->refcount, ==, 0);
  munit_assert_int(arr->refcount, ==, 0);

  return MUNIT_OK;
}

MunitResult test_array_free() {
  snek_object_t *foo = new_snek_integer(1);
  snek_object_t *bar = new_snek_integer(2);
  snek_object_t *baz = new_snek_integer(3);

  snek_object_t *arr = new_snek_array(2);
  snek_array_set(arr, 0, foo);
  snek_array_set(arr, 1, bar);
  munit_assert_int(foo->refcount, ==, 2);
  munit_assert_int(bar->refcount, ==, 2);
  munit_assert_int(baz->refcount, ==, 1);

  refcount_dec(foo);
  snek_array_set(arr, 0, baz);

  munit_assert_int(foo->refcount, ==, 0);
  refcount_dec(bar);
  refcount_dec(baz);
  refcount_dec(arr);
  return MUNIT_OK;
}

MunitResult test_get_outside_bound() {
  snek_object_t *obj = new_snek_array(1);
  snek_object_t *first = new_snek_string("hello");
  munit_assert(snek_array_set(obj, 0, first));

  munit_assert_null(snek_array_get(obj, 1));

  free(first->data.v_string);
  free(first);
  free(obj->data.v_array.elements);
  free(obj);
  return MUNIT_OK;
}

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
