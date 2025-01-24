#include <stdio.h>
#include <stdlib.h>
#include "list/list.h"

int main()
{
  List l = lst_create((int[]) {2, 3}, 0);
  lst_push_back(&l, 1);

  lst_print(l);
  return 0;
}
