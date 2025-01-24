#include "list.h"

static _Node *_lst_create_node(int data)
{
  _Node *node = malloc(sizeof(_Node));
  node->data = data;
  node->next = NULL;
  return node;
}

static void _lst_destroy_node(_Node *node)
{
  free(node);
}

static _Node *_lst_get_node_forward(_Node *node, size_t forward)
{
  _Node *forwardNode = node;
  for (size_t i = 0; i < forward; i++)
  {
    forwardNode = forwardNode->next;
  }

  return forwardNode;
}

List lst_create_empty()
{
  return (List){NULL, 0, NULL};
}

List lst_create(int *values, size_t length)
{
  List lst = lst_create_empty();

  if (values == NULL || length == 0)
  {
    return lst;
  }

  _Node *node = _lst_create_node(values[0]);
  lst._start = node;
  for (size_t i = 1; i < length; i++)
  {
    _Node *nextNode = _lst_create_node(values[i]);
    node->next = nextNode;
    node = nextNode;
  }
  lst.size = length;
  lst._end = node;

  return lst;
}

void lst_destroy(List *lst)
{
  lst_clear(lst);
}

void lst_push_front(List *lst, int value)
{
  _Node *newNode = _lst_create_node(value);

  newNode->next = lst->_start;
  lst->_start = newNode;
  if (lst->_end == NULL)
  {
    lst->_end = newNode;
  }

  lst->size++;
}

void lst_push_back(List *lst, int value)
{
  _Node *newNode = _lst_create_node(value);

  if (lst->_end)
  {
    lst->_end->next = newNode;
  }
  lst->_end = newNode;
  if (lst->_start == NULL)
  {
    lst->_start = newNode;
  }

  lst->size++;
}

void lst_insert(List *lst, int value, size_t position)
{
  if (lst->size < position)
  {
    return;
  }

  if (position == 0)
  {
    return lst_push_front(lst, value);
  }
  if (position == lst->size)
  {
    return lst_push_back(lst, value);
  }

  _Node *newNode = _lst_create_node(value);
  _Node *nodeAt = _lst_get_node_forward(lst->_start, position - 1);
  newNode->next = nodeAt->next;
  nodeAt->next = newNode;

  lst->size++;
}

int lst_pop_front(List *lst)
{
  if (lst_empty(*lst))
  {
    return NULL;
  }

  _Node *firstNode = lst->_start;
  lst->_start = firstNode->next;

  int data = firstNode->data;
  _lst_destroy_node(firstNode);
  lst->size--;
  return data;
}

int lst_pop_back(List *lst)
{
  if (lst_empty(*lst))
  {
    return NULL;
  }

  _Node *lastNode;
  if (lst->size == 1)
  {
    lastNode = lst->_start;
    lst->_start = NULL;
    lst->_end = NULL;
  }
  else
  {
    _Node *prevLastNode = _lst_get_node_forward(lst->_start, lst->size - 1 - 1);
    lastNode = prevLastNode->next;
    prevLastNode->next = NULL;
    lst->_end = prevLastNode;
  }

  int data = lastNode->data;
  _lst_destroy_node(lastNode);
  lst->size--;
  return data;
}

int lst_remove(List *lst, int value)
{
  _Node *prevNode = NULL;
  _Node *currentNode = lst->_start;

  while (currentNode != NULL)
  {
    if (currentNode->data == value)
    {
      if (prevNode == NULL)
      {
        lst->_start = currentNode->next;
      }
      else
      {
        prevNode->next = currentNode->next;
      }

      if (currentNode->next == NULL)
      {
        lst->_end = prevNode;
      }

      _lst_destroy_node(currentNode);
      lst->size--;
      return 1; // true
    }

    prevNode = currentNode;
    currentNode = currentNode->next;
  }

  return 0; // false
}

int lst_remove_at(List *lst, size_t position)
{
  if (position < 0 || lst->size <= position)
  {
    return NULL;
  }

  if (position == 0)
  {
    return lst_pop_front(lst);
  }
  if (position == lst->size - 1)
  {
    return lst_pop_back(lst);
  }

  _Node *nodeToDelete;
  _Node *prevNode = _lst_get_node_forward(lst->_start, position - 1);
  nodeToDelete = prevNode->next;
  prevNode->next = nodeToDelete->next;

  int data = nodeToDelete->data;
  _lst_destroy_node(nodeToDelete);
  lst->size--;
  return data;
}

int lst_at(List lst, size_t position)
{
  if (position < 0 || lst.size <= position)
  {
    return NULL;
  }

  _Node *node = _lst_get_node_forward(lst._start, position);
  return node->data;
}

void lst_print(List lst)
{
  if (lst_empty(lst))
  {
    printf("[]");
    return;
  }

  _Node *current = lst._start;

  printf("[");
  while (current->next)
  {
    printf("%d, ", current->data);
    current = _lst_get_node_forward(current, 1);
  }
  printf("%d]", current->data);
}

void lst_clear(List *lst)
{
  _Node *current = lst->_start;
  while (current != NULL)
  {
    _Node *next = current->next;
    _lst_destroy_node(current);
    current = next;
  }

  lst->_start = NULL;
  lst->size = 0;
  lst->_end = NULL;
}

int lst_front(List lst)
{
  if (lst_empty(lst))
  {
    return NULL;
  }

  return lst._start->data;
}

int lst_end(List lst)
{
  if (lst_empty(lst))
  {
    return NULL;
  }

  return lst._end->data;
}

size_t lst_size(List lst)
{
  return lst.size;
}

int lst_empty(List lst)
{
  return lst.size == 0;
}

void lst_swap(List *lst, size_t position1, size_t position2)
{
  if (position1 == position2)
  {
    return;
  }

  size_t lowerPos = (position1 <= position2) ? position1 : position2;
  size_t higherPos = (position1 > position2) ? position1 : position2;

  if (lowerPos < 0 || lst->size <= higherPos)
  {
    return;
  }

  _Node *prevLowerNode;
  _Node *lowerNode;

  if (lowerPos == 0)
  {
    prevLowerNode = NULL;
    lowerNode = lst->_start;
  }
  else
  {
    prevLowerNode = _lst_get_node_forward(lst->_start, lowerPos - 1);
    lowerNode = prevLowerNode->next;
  }

  _Node *prevHigherNode = _lst_get_node_forward(lowerNode, higherPos - lowerPos - 1);
  _Node *higherNode = prevHigherNode->next;

  if (lowerPos == 0)
  {
    lst->_start = higherNode;
  }
  else
  {
    prevLowerNode->next = higherNode;
  }
  prevHigherNode->next = lowerNode;

  _Node *tempNode = lowerNode->next;
  lowerNode->next = higherNode->next;
  higherNode->next = tempNode;

  if (higherPos == lst->size - 1)
  {
    lst->_end = lowerNode;
  }
}
