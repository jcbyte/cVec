#include "../include/vector.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

Vector vec_create_empty()
{
  return (Vector){NULL, 0, 0};
}

Vector vec_create(int *values, size_t length)
{
  size_t bytes = sizeof(int) * length;
  int *arr = malloc(bytes);
  memcpy(arr, values, bytes);

  return (Vector){arr, length, length};
}

void vec_destroy(Vector *vec)
{
  free(vec->_arr);
}

void vec_push_front(Vector *vec, int value) {}
void vec_push_back(Vector *vec, int value) {}
void vec_insert(Vector *vec, int value, size_t position) {}
int vec_pop_front(Vector *vec) {}
int vec_pop_back(Vector *vec) {}
int vec_remove(Vector *vec, int value) {}
int vec_remove_at(Vector *vec, size_t position) {}

int vec_at(Vector vec, size_t position)
{
  if (position < 0 || vec.size <= position)
  {
    errno = EINVAL;
    return -1; // Note: -1 could also be returned on success
  }

  return vec._arr[position];
}

void vec_print(Vector vec)
{
  if (vec_empty(vec))
  {
    printf("[]");
    return;
  }

  printf("[");
  for (int i = 0; i < vec.size - 1; i++)
  {
    printf("%d, ", vec._arr[i]);
  }
  printf("%d]", vec._arr[vec.size - 1]);
}

void vec_clear(Vector *vec)
{
  vec->size = 0;
}

int vec_front(Vector vec)
{
  if (vec_empty(vec))
  {
    errno = EINVAL;
    return -1; // Note: -1 could also be returned on success
  }

  return vec._arr[0];
}

int vec_end(Vector vec)
{
  if (vec_empty(vec))
  {
    errno = EINVAL;
    return -1; // Note: -1 could also be returned on success
  }

  return vec._arr[vec.size - 1];
}

size_t vec_size(Vector vec)
{
  return vec.size;
}
size_t vec_capacity(Vector vec)
{
  return vec.capacity;
}

void vec_shrink_to_fit(Vector *vec) {}

int vec_empty(Vector vec)
{
  return vec.size == 0;
}

void vec_swap(Vector *vec, size_t position1, size_t position2) {}
