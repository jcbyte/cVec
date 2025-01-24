#include <stdio.h>
#include <stdlib.h>
#include "list/list.h"

int main()
{
  List l = lst_create((int[]) {1, 2, 3}, 3);

  // todo exmaple code
  lst_print(l);
  
  lst_destroy(&l);
  return 0;
}
