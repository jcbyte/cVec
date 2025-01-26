#pragma once

#include <stdlib.h>

typedef struct _Node
{
  int data;
  struct _Node *next;
} _Node;

typedef struct List
{
  _Node *_start;
  size_t size;
  _Node *_end;
} List;

List lst_create_empty();
List lst_create(int *values, size_t length);
void lst_destroy(List *lst);

void lst_push_front(List *lst, int value);
void lst_push_back(List *lst, int value);
void lst_insert(List *lst, int value, size_t position);

int lst_pop_front(List *lst);
int lst_pop_back(List *lst);
int lst_remove(List *lst, int value);
int lst_remove_at(List *lst, size_t position);

int lst_at(List lst, size_t position);
void lst_print(List lst);

void lst_clear(List *lst);
int lst_front(List lst);
int lst_end(List lst);
size_t lst_size(List lst);
int lst_empty(List lst);
void lst_swap(List *lst, size_t position1, size_t position2);
