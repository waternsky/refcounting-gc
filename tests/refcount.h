#pragma once
#include "../munit/munit.h"

MunitResult test_int_has_refcount();
MunitResult test_float_has_refcount();
MunitResult test_inc_refcount();
MunitResult test_dec_refcount();
MunitResult test_free_refcount();
MunitResult test_vector3_refcounting();
MunitResult test_vector3_refcounting_same();
