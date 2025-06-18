#include "snekobject.h"
#include <stdlib.h>
#include <string.h>

snek_object_t *_new_snek_object() {
  snek_object_t *obj = (snek_object_t *)calloc(1, sizeof(snek_object_t));
  if (obj == NULL)
    return NULL;
  obj->refcount = 1;
  return obj;
}

snek_object_t *new_snek_array(size_t size) {
  snek_object_t *obj = _new_snek_object();
  if (obj == NULL)
    return NULL;
  snek_object_t **elements =
      (snek_object_t **)calloc(size, sizeof(snek_object_t *));
  if (elements == NULL) {
    free(obj);
    return NULL;
  }
  obj->kind = ARRAY;
  obj->data.v_array = (snek_array_t){.size = size, .elements = elements};
  return obj;
}

snek_object_t *new_snek_vector3(snek_object_t *x, snek_object_t *y,
                                snek_object_t *z) {
  if (x == NULL || y == NULL || z == NULL)
    return NULL;
  snek_object_t *obj = _new_snek_object();
  if (obj == NULL)
    return NULL;
  obj->kind = VECTOR3;
  obj->data.v_vector3 = (snek_vector_t){.x = x, .y = y, .z = z};
  return obj;
}

snek_object_t *new_snek_integer(int value) {
  snek_object_t *obj = _new_snek_object();
  if (obj == NULL)
    return NULL;
  obj->kind = INTEGER;
  obj->data.v_int = value;
  return obj;
}

snek_object_t *new_snek_float(float value) {
  snek_object_t *obj = _new_snek_object();
  if (obj == NULL)
    return NULL;
  obj->kind = FLOAT;
  obj->data.v_float = value;
  return obj;
}

snek_object_t *new_snek_string(char *value) {
  snek_object_t *obj = _new_snek_object();
  if (obj == NULL)
    return NULL;
  char *str = (char *)calloc(strlen(value) + 1, sizeof(char));
  if (str == NULL) {
    free(obj);
    return NULL;
  }
  strcpy(str, value);
  obj->kind = STRING;
  obj->data.v_string = str;
  return obj;
}
