#include <stdio.h>
#include <stdlib.h>
#include "../include/vector.h"
#include <errno.h>

int main()
{
  Vector v = vec_create_empty();
  // Vector v = vec_create((int[]){10, 20, 40}, 3);
  vec_print(v);
  vec_push_front(&v, 1);
  vec_print(v);
  vec_push_front(&v, 2);
  vec_print(v);
  vec_push_front(&v, 3);
  vec_print(v);
  int a = vec_pop_front(&v);
  vec_print(v);

  printf("\n\n");
  return 0;
}
