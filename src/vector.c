#include "../include/vector.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

size_t _vec_get_next_capacity(size_t capacity)
{
  if (capacity == 0)
  {
    return 1;
  }

  return capacity * 2;
}

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

void vec_push_front(Vector *vec, int value)
{
  if (vec->capacity <= vec->size)
  {
    size_t new_capacity = _vec_get_next_capacity(vec->capacity);

    int *new_arr = malloc(sizeof(int) * new_capacity);
    memcpy(new_arr + 1, vec->_arr, sizeof(int) * vec->size);

    free(vec->_arr);
    vec->_arr = new_arr;
    vec->capacity = new_capacity;
  }
  else
  {
    memmove(vec->_arr + 1, vec->_arr, sizeof(int) * vec->size);
  }
  vec->_arr[0] = value;
  vec->size++;
}

void vec_push_back(Vector *vec, int value)
{
  if (vec->capacity <= vec->size)
  {
    size_t new_capacity = _vec_get_next_capacity(vec->capacity);

    int *new_arr = malloc(sizeof(int) * new_capacity);
    memcpy(new_arr, vec->_arr, sizeof(int) * vec->size);

    free(vec->_arr);
    vec->_arr = new_arr;
    vec->capacity = new_capacity;
  }

  vec->_arr[vec->size] = value;
  vec->size++;
}

void vec_insert(Vector *vec, int value, size_t position)
{
  if (position < 0 || vec->size < position)
  {
    errno = EINVAL;
    return;
  }

  if (vec->capacity <= vec->size)
  {
    size_t new_capacity = _vec_get_next_capacity(vec->capacity);

    int *new_arr = malloc(sizeof(int) * new_capacity);
    memcpy(new_arr, vec->_arr, sizeof(int) * (position));
    memcpy(new_arr + position + 1, vec->_arr + position, sizeof(int) * (vec->size - position));

    free(vec->_arr);
    vec->_arr = new_arr;
    vec->capacity = new_capacity;
  }
  else
  {
    memmove(vec->_arr + position + 1, vec->_arr + position, sizeof(int) * (vec->size - position));
  }

  vec->_arr[position] = value;
  vec->size++;
}

int vec_pop_front(Vector *vec)
{
  if (vec_empty(*vec))
  {
    errno = EINVAL;
    return -1; // Note: -1 could also be returned on success
  }

  int value = vec->_arr[0];
  vec->size--;
  memmove(vec->_arr, vec->_arr + 1, sizeof(int) * vec->size);
  return value;
}

int vec_pop_back(Vector *vec)
{
  if (vec_empty(*vec))
  {
    errno = EINVAL;
    return -1; // Note: -1 could also be returned on success
  }

  vec->size--;
  return vec->_arr[vec->size];
}

int vec_remove(Vector *vec, int value)
{
  for (int i = 0; i < vec->size; i++)
  {
    if (vec->_arr[i] == value)
    {
      vec_remove_at(vec, i);
      return 1; // true
    }
  }

  return 0; // false
}

int vec_remove_at(Vector *vec, size_t position)
{
  if (position < 0 || vec->size <= position)
  {
    errno = EINVAL;
    return -1; // Note: -1 could also be returned on success
  }

  int value = vec->_arr[position];
  vec->size--;
  memmove(vec->_arr + position, vec->_arr + position + 1, sizeof(int) * (vec->size - position));
  return value;
}

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

void vec_shrink_to_fit(Vector *vec)
{
  int *new_arr = malloc(sizeof(int) * vec->size);
  memcpy(new_arr, vec->_arr, sizeof(int) * vec->size);

  free(vec->_arr);
  vec->_arr = new_arr;
  vec->capacity = vec->size;
}

int vec_empty(Vector vec)
{
  return vec.size == 0;
}

void vec_swap(Vector *vec, size_t position1, size_t position2)
{
  if (position1 == position2)
  {
    return;
  }

  if (position1 < 0 || vec->size <= position1 || position2 < 0 || vec->size <= position2)
  {
    errno = EINVAL;
    return;
  }

  int temp = vec->_arr[position1];
  vec->_arr[position1] = vec->_arr[position2];
  vec->_arr[position2] = temp;
}
