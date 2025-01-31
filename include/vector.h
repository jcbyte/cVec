#pragma once

#include <stdlib.h>

// Vector structure representing the dynamic array.
typedef struct Vector
{
  int *_arr;
  size_t size;
  size_t capacity;
} Vector;

/**
 * @brief Creates an empty vector.
 *
 * @return A new empty vector.
 */
Vector vec_create_empty();

/**
 * @brief Creates a vector from an array of integers.
 *
 * @param values Array of integers to initialize the vector with.
 * @param length The number of elements in the values array.
 *
 * @return A new vector containing the values from the array.
 */
Vector vec_create(int *values, size_t length);

/**
 * @brief Destroys the vector and frees its memory.
 *
 * @param vec Pointer to the vector to be destroyed.
 */
void vec_destroy(Vector *vec);

/**
 * @brief Adds a new element to the front of the vector.
 *
 * @param vec Pointer to the vector.
 * @param value The value to add to the front.
 */
void vec_push_front(Vector *vec, int value);

/**
 * @brief Adds a new element to the back of the vector.
 *
 * @param vec Pointer to the vector.
 * @param value The value to add to the back.
 */
void vec_push_back(Vector *vec, int value);

/**
 * @brief Inserts a value at a specific position in the vector.
 *
 * @param vec Pointer to the vector.
 * @param value The value to insert.
 * @param position The position at which to insert the value.
 */
void vec_insert(Vector *vec, int value, size_t position);

/**
 * @brief Removes and returns the element at the front of the vector.
 *
 * @param vec Pointer to the vector.
 *
 * @return The value of the removed element.
 */
int vec_pop_front(Vector *vec);

/**
 * @brief Removes and returns the element at the back of the vector.
 *
 * @param vec Pointer to the vector.
 *
 * @return The value of the removed element.
 */
int vec_pop_back(Vector *vec);

/**
 * @brief Removes the first occurrence of a specific value from the vector.
 *
 * @param vec Pointer to the vector.
 * @param value The value to remove.
 *
 * @return True if the value was found and removed.
 */
int vec_remove(Vector *vec, int value);

/**
 * @brief Removes the element at a specific position in the vector.
 *
 * @param vec Pointer to the vector.
 * @param position The position of the element to remove.
 *
 * @return The value of the removed element.
 */
int vec_remove_at(Vector *vec, size_t position);

/**
 * @brief Retrieves the value at a specific position in the vector.
 *
 * @param vec The vector.
 * @param position The position to retrieve the value from.
 *
 * @return The value at the specified position.
 */
int vec_at(Vector vec, size_t position);

/**
 * @brief Prints the vector's contents to the standard output.
 *
 * @param vec The vector to print.
 */
void vec_print(Vector vec);

/**
 * @brief Clears the vector, removing all elements.
 *
 * @param vec Pointer to the vector.
 */
void vec_clear(Vector *vec);

/**
 * @brief Retrieves the value of the first element in the vector.
 *
 * @param vec The vector.
 *
 * @return The value of the first element.
 */
int vec_front(Vector vec);

/**
 * @brief Retrieves the value of the last element in the vector.
 *
 * @param vec The vector.
 *
 * @return The value of the last element.
 */
int vec_end(Vector vec);

/**
 * @brief Retrieves the number of elements in the vector.
 *
 * @param vec The vector.
 *
 * @return The number of elements in the vector.
 */
size_t vec_size(Vector vec);

/**
 * @brief Retrieves the capacity of the underlying array in the vector.
 *
 * @param vec The vector.
 *
 * @return The capacity of the underlying array in the vector.
 */
size_t vec_capacity(Vector vec);

/**
 * @brief Shrinks the underlying array in the vector to its current size.
 *
 * @param vec The vector.
 */
void vec_shrink_to_fit(Vector *vec);

/**
 * @brief Checks if the vector is empty.
 *
 * @param vec Pointer to the vector.
 *
 * @return True if the list is empty.
 */
int vec_empty(Vector vec);

/**
 * @brief Swaps two elements in the vector at the specified positions.
 *
 * @param vec Pointer to the vector.
 * @param position1 The first position to swap.
 * @param position2 The second position to swap.
 */
void vec_swap(Vector *vec, size_t position1, size_t position2);
