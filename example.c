#include <stdio.h>
#include <stdlib.h>
#include "list/list.h"

int main()
{
  List l = lst_create((int[]) {10, 20, 30}, 3);
  int r = lst_remove_at(&l, -1);

  lst_print(l);
  return 0;
}
