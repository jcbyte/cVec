#include <stdio.h>
#include <stdlib.h>
#include "../include/vector.h"
#include <errno.h>

int main()
{
  // Vector v = vec_create_empty();
  Vector v = vec_create((int[]){10, 20, 40}, 3);

  return 0;
}
