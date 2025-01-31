#include <stdio.h>
#include <stdlib.h>
#include "../include/vector.h"
#include <errno.h>

int main()
{
  // Vector v = vec_create_empty();
  Vector v = vec_create((int[]){10, 20, 30}, 3);
  vec_print(v);
  vec_push_back(&v, 40);
  vec_print(v);
  vec_shrink_to_fit(&v);
  vec_print(v);

  printf("\n\n");
  return 0;
}
