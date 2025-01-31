#include <stdio.h>
#include <stdlib.h>
#include "../include/vector.h"
#include <errno.h>

int main()
{
  // Create a vector with pre-initialised values
  Vector v = vec_create((int[]){10, 20, 40}, 3);

  // Add elements to the vector
  vec_push_back(&v, 50);
  vec_insert(&v, 30, 2);

  // Get elements at specific positions of list
  for (int i = 0; i < vec_size(v); i++)
  {
    printf("Element at position %d: %d\n", i, vec_at(v, i));
  }
  printf("\n");

  // Print the list for debugging
  vec_print(v);
  printf("\n\n");

  // Remove elements by value
  if (vec_remove(&v, 30))
  {
    printf("Removed element 30\n");
  }

  vec_print(v);
  printf("\n\n");

  // Remove element by index
  int value = vec_remove_at(&v, 420);
  // Error handling
  if (errno)
  {
    printf("Error removing element at 420\n\n");
  }

  // Swap elemets in list
  vec_swap(&v, 0, 2);
  vec_print(v);
  printf("\n\n");

  // Shrink underlying structure to save memory
  vec_shrink_to_fit(&v);

  // Clean up resources used by the vector
  vec_destroy(&v);
  return 0;
}