#include <stdio.h>
#include <stdlib.h>
#include "../include/vector.h"
#include <errno.h>

int main()
{
  Vector v = vec_create_empty();
  // Vector v = vec_create((int[]){10, 20, 40}, 3);
  vec_print(v);
  vec_insert(&v, 1, 0);
  vec_print(v);
  vec_insert(&v, 2, 0);
  vec_print(v);
  vec_insert(&v, 3, 0);
  vec_print(v);
  vec_insert(&v, 4, 0);
  vec_print(v);

  printf("\n\n");
  return 0;
}
