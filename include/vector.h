#pragma once

#pragma once

#include <stdlib.h>

typedef struct Vector
{
  int *_arr;
  size_t size;
  size_t capacity;
} Vector;

Vector vec_create_empty();
Vector vec_create(int *values, size_t length);
void vec_destroy(Vector *vec);
void vec_push_front(Vector *vec, int value);
void vec_push_back(Vector *vec, int value);
void vec_insert(Vector *vec, int value, size_t position);
int vec_pop_front(Vector *vec);
int vec_pop_back(Vector *vec);
int vec_remove(Vector *vec, int value);
int vec_remove_at(Vector *vec, size_t position);
int vec_at(Vector vec, size_t position);
void vec_print(Vector vec);
void vec_clear(Vector *vec);
int vec_front(Vector vec);
int vec_end(Vector vec);
size_t vec_size(Vector vec);
size_t vec_capacity(Vector vec);
void vec_shrink_to_fit(Vector *vec);
int vec_empty(Vector vec);
void vec_swap(Vector *vec, size_t position1, size_t position2);
