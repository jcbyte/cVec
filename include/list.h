#pragma once

#include <stdlib.h>

// Node structure for a singly linked list.
// This should not be used directly by the user.
typedef struct _Node
{
  int data;
  struct _Node *next;
} _Node;

// List structure representing the linked list.
typedef struct List
{
  _Node *_start;
  size_t size;
  _Node *_end;
} List;

/**
 * @brief Creates an empty list.
 *
 * @return A new empty list.
 */
List lst_create_empty();

/**
 * @brief Creates a list from an array of integers.
 *
 * @param values Array of integers to initialize the list with.
 * @param length The number of elements in the values array.
 *
 * @return A new list containing the values from the array.
 */
List lst_create(int *values, size_t length);

/**
 * @brief Destroys the list and frees its memory.
 *
 * @param lst Pointer to the list to be destroyed.
 */
void lst_destroy(List *lst);

/**
 * @brief Adds a new element to the front of the list.
 *
 * @param lst Pointer to the list.
 * @param value The value to add to the front.
 */
void lst_push_front(List *lst, int value);

/**
 * @brief Adds a new element to the back of the list.
 *
 * @param lst Pointer to the list.
 * @param value The value to add to the back.
 */
void lst_push_back(List *lst, int value);

/**
 * @brief Inserts a value at a specific position in the list.
 *
 * @param lst Pointer to the list.
 * @param value The value to insert.
 * @param position The position at which to insert the value.
 */
int lst_insert(List *lst, int value, size_t position);

/**
 * @brief Removes and returns the element at the front of the list.
 *
 * @param lst Pointer to the list.
 *
 * @return The value of the removed element.
 */
int lst_pop_front(List *lst);

/**
 * @brief Removes and returns the element at the back of the list.
 *
 * @param lst Pointer to the list.
 *
 * @return The value of the removed element.
 */
int lst_pop_back(List *lst);

/**
 * @brief Removes the first occurrence of a specific value from the list.
 *
 * @param lst Pointer to the list.
 * @param value The value to remove.
 *
 * @return True if the value was found and removed.
 */
int lst_remove(List *lst, int value);

/**
 * @brief Removes the element at a specific position in the list.
 *
 * @param lst Pointer to the list.
 * @param position The position of the element to remove.
 *
 * @return The value of the removed element.
 */
int lst_remove_at(List *lst, size_t position);

/**
 * @brief Retrieves the value at a specific position in the list.
 *
 * @param lst The list.
 * @param position The position to retrieve the value from.
 *
 * @return The value at the specified position.
 */
int lst_at(List lst, size_t position);

/**
 * @brief Prints the list's contents to the standard output.
 *
 * @param lst The list to print.
 */
void lst_print(List lst);

/**
 * @brief Clears the list, removing all elements.
 *
 * @param lst Pointer to the list.
 */
void lst_clear(List *lst);

/**
 * @brief Retrieves the value of the first element in the list.
 *
 * @param lst The list.
 *
 * @return The value of the first element.
 */
int lst_front(List lst);

/**
 * @brief Retrieves the value of the last element in the list.
 *
 * @param lst The list.
 *
 * @return The value of the last element.
 */
int lst_end(List lst);

/**
 * @brief Retrieves the number of elements in the list.
 *
 * @param lst The list.
 *
 * @return The number of elements in the list.
 */
size_t lst_size(List lst);

/**
 * @brief Checks if the list is empty.
 *
 * @param lst The list.
 *
 * @return True if the list is empty.
 */
int lst_empty(List lst);

/**
 * @brief Swaps two elements in the list at the specified positions.
 *
 * @param lst Pointer to the list.
 * @param position1 The first position to swap.
 * @param position2 The second position to swap.
 */
int lst_swap(List *lst, size_t position1, size_t position2);
