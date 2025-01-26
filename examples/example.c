#include <stdio.h>
#include <stdlib.h>
#include "../include/list.h"
#include <errno.h>

int main()
{
  // todo create examples
  List l = lst_create((int[]) {1, 2, 3}, 3);

  lst_insert(&l, 4, 10);
  lst_print(l);
  
  lst_destroy(&l);
  return 0;
}
