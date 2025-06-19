#pragma once
#include "../munit/munit.h"

MunitResult test_integer_positive();
MunitResult test_integer_zero();
MunitResult test_integer_negative();

MunitResult test_float_positive();
MunitResult test_float_zero();
MunitResult test_float_negative();

MunitResult test_string_copied();

MunitResult test_vector3_null();
MunitResult test_vector3_multiple_objects();
MunitResult test_vector3_same_object();

MunitResult test_create_empty_array();
MunitResult test_array_used_calloc();
