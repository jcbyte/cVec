#include <stdio.h>
#include "../include/list.h"
#include <errno.h>

int main()
{
  // Create a list with pre-initialised values
  List l = lst_create((int[]){10, 20, 40}, 3);

  // Add elements to the list
  lst_push_back(&l, 50);
  lst_insert(&l, 30, 2);

  // Get elements at specific positions of list
  for (int i = 0; i < lst_size(l); i++)
  {
    printf("Element at position %d: %d\n", i, lst_at(l, i));
  }
  printf("\n");

  // Print the list for debugging
  lst_print(l);
  printf("\n\n");

  // Remove elements by value
  if (lst_remove(&l, 30))
  {
    printf("Removed element 30\n");
  }

  lst_print(l);
  printf("\n\n");

  // Remove element by index
  int value = lst_remove_at(&l, 420);
  // Error handling
  if (errno)
  {
    printf("Error removing element at 420\n\n");
  }

  // Swap elemets in list
  lst_swap(&l, 0, 2);
  lst_print(l);
  printf("\n\n");

  // Clean up resources used by the list
  lst_destroy(&l);
  return 0;
}
