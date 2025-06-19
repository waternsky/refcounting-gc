#include "../munit/munit.h"
#include "../snekobject.h"

MunitResult test_integer_positive() {
  snek_object_t *integer = new_snek_integer(42);
  munit_assert_int(integer->kind, ==, INTEGER);
  munit_assert_int(integer->data.v_int, ==, 42);
  free(integer);
  return MUNIT_OK;
}

MunitResult test_integer_zero() {
  snek_object_t *integer = new_snek_integer(0);
  munit_assert_int(integer->kind, ==, INTEGER);
  munit_assert_int(integer->data.v_int, ==, 0);
  free(integer);
  return MUNIT_OK;
}

MunitResult test_integer_negative() {
  snek_object_t *integer = new_snek_integer(-5);
  munit_assert_int(integer->kind, ==, INTEGER);
  munit_assert_int(integer->data.v_int, ==, -5);
  free(integer);
  return MUNIT_OK;
}

MunitResult test_float_positive() {
  snek_object_t *f = new_snek_float(42.0);
  munit_assert_int(f->kind, ==, FLOAT);
  munit_assert_float(f->data.v_float, ==, 42.0);
  free(f);
  return MUNIT_OK;
}

MunitResult test_float_zero() {
  snek_object_t *f = new_snek_float(0);
  munit_assert_int(f->kind, ==, FLOAT);
  munit_assert_float(f->data.v_float, ==, 0.0);
  free(f);
  return MUNIT_OK;
}

MunitResult test_float_negative() {
  snek_object_t *f = new_snek_float(-5.0);
  munit_assert_int(f->kind, ==, FLOAT);
  munit_assert_float(f->data.v_float, ==, -5.0);
  free(f);
  return MUNIT_OK;
}

MunitResult test_string_copied() {
  char *input = "Hello, World!";
  snek_object_t *obj = new_snek_string(input);
  munit_assert_int(obj->kind, ==, STRING);
  munit_assert_ptr_not_equal(obj->data.v_string, input);
  munit_assert_string_equal(obj->data.v_string, input);
  free(obj->data.v_string);
  free(obj);
  return MUNIT_OK;
}

MunitResult test_create_empty_array() {
  snek_object_t *obj = new_snek_array(2);
  munit_assert_int(obj->kind, ==, ARRAY);
  munit_assert_ulong(obj->data.v_array.size, ==, 2);
  free(obj->data.v_array.elements);
  free(obj);
  return MUNIT_OK;
}

MunitResult test_array_used_calloc() {
  snek_object_t *obj = new_snek_array(2);
  munit_assert_ptr_null(obj->data.v_array.elements[0]);
  munit_assert_ptr_null(obj->data.v_array.elements[1]);
  free(obj->data.v_array.elements);
  free(obj);
  return MUNIT_OK;
}

MunitResult test_vector3_null() {
  snek_object_t *obj = new_snek_vector3(NULL, NULL, NULL);
  munit_assert_null(obj);
  free(obj);
  return MUNIT_OK;
}

MunitResult test_vector3_multiple_objects() {
  snek_object_t *x = new_snek_integer(1);
  snek_object_t *y = new_snek_integer(2);
  snek_object_t *z = new_snek_integer(3);
  snek_object_t *vec = new_snek_vector3(x, y, z);

  munit_assert_not_null(vec);

  munit_assert_ptr(x, ==, vec->data.v_vector3.x);
  munit_assert_ptr(y, ==, vec->data.v_vector3.y);
  munit_assert_ptr(z, ==, vec->data.v_vector3.z);

  munit_assert_int(vec->data.v_vector3.x->data.v_int, ==, 1);
  munit_assert_int(vec->data.v_vector3.y->data.v_int, ==, 2);
  munit_assert_int(vec->data.v_vector3.z->data.v_int, ==, 3);

  free(x);
  free(y);
  free(z);
  free(vec);
  return MUNIT_OK;
}

MunitResult test_vector3_same_object() {
  snek_object_t *i = new_snek_integer(1);
  snek_object_t *vec = new_snek_vector3(i, i, i);

  munit_assert_ptr_not_null(vec);

  munit_assert_ptr(i, ==, vec->data.v_vector3.x);
  munit_assert_ptr(i, ==, vec->data.v_vector3.y);
  munit_assert_ptr(i, ==, vec->data.v_vector3.z);

  munit_assert_int(vec->data.v_vector3.x->data.v_int, ==, 1);
  munit_assert_int(vec->data.v_vector3.y->data.v_int, ==, 1);
  munit_assert_int(vec->data.v_vector3.z->data.v_int, ==, 1);

  i->data.v_int = 2;

  munit_assert_int(vec->data.v_vector3.x->data.v_int, ==, 2);
  munit_assert_int(vec->data.v_vector3.y->data.v_int, ==, 2);
  munit_assert_int(vec->data.v_vector3.z->data.v_int, ==, 2);

  free(i);
  free(vec);
  return MUNIT_OK;
}
