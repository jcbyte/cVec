#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main()
{
	List lst = lst_create();

	lst_push_back(&lst, 2);
	lst_push_back(&lst, 4);
	lst_push_front(&lst, 1);
	lst_insert(&lst, 3, 2);

	lst_print(lst);
	printf("\n");

	lst_swap(&lst, 2, 1);
	lst_print(lst);

	return 0;
}
