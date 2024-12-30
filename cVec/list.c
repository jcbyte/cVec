#include "list.h"

List lst_create()
{
	return (List) { NULL, 0 };
}

static _Node* _lst_create_node(int data)
{
	_Node* node = malloc(sizeof(_Node));
	node->data = data;
	node->next = NULL;
	return node;
}

static void _lst_delete_node(_Node* node)
{
	free(node);
}

static _Node* _lst_get_node_forward(_Node* node, size_t forward)
{
	_Node* forwardNode = node;
	for (int i = 0; i < forward; i++)
	{
		forwardNode = forwardNode->next;
	}

	return forwardNode;
}

void lst_push_front(List* lst, int value)
{
	_Node* newNode = _lst_create_node(value);

	newNode->next = lst->_start;
	lst->_start = newNode;

	lst->size++;
}

void lst_push_back(List* lst, int value)
{
	_Node* newNode = _lst_create_node(value);

	if (lst->size == 0)
	{
		lst->_start = newNode;
	}
	else
	{
		_Node* lastNode = _lst_get_node_forward(lst->_start, lst->size - 1);
		lastNode->next = newNode;
	}

	lst->size++;
}

void lst_insert(List* lst, int value, size_t position)
{
	if (lst->size < position)
	{
		return;
	}

	_Node* newNode = _lst_create_node(value);

	if (position == 0)
	{
		newNode->next = lst->_start;
		lst->_start = newNode;
	}
	else
	{
		_Node* nodeAt = _lst_get_node_forward(lst->_start, position - 1);
		newNode->next = nodeAt->next;
		nodeAt->next = newNode;
	}

	lst->size++;
}

int lst_pop_front(List* lst)
{
	if (lst_empty(*lst))
	{
		return NULL;
	}

	_Node* firstNode = lst->_start;
	lst->_start = firstNode->next;

	int data = firstNode->data;
	_lst_delete_node(firstNode);
	lst->size--;
	return data;
}

int lst_pop_back(List* lst)
{
	if (lst_empty(*lst))
	{
		return NULL;
	}

	_Node* prevLastNode = _lst_get_node_forward(lst->_start, lst->size - 1 - 1);
	_Node* lastNode = prevLastNode->next;
	prevLastNode->next = NULL;

	int data = lastNode->data;
	_lst_delete_node(lastNode);
	lst->size--;
	return data;
}

int lst_remove(List* lst, int value)
{
	_Node* prevNode = NULL;
	_Node* currentNode = lst->_start;

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

			int data = currentNode->data;
			_lst_delete_node(currentNode);
			lst->size--;
			return data;
		}

		prevNode = currentNode;
		currentNode = currentNode->next;
	}
}

int lst_remove_at(List* lst, size_t position)
{
	if (lst->size <= position)
	{
		return NULL;
	}

	_Node* nodeToDelete;
	if (position == 0)
	{
		nodeToDelete = lst->_start;
		lst->_start = nodeToDelete->next;
	}
	else
	{
		_Node* prevNode = _lst_get_node_forward(lst->_start, position - 1);
		nodeToDelete = prevNode->next;
		prevNode->next = nodeToDelete->next;
	}

	int data = nodeToDelete->data;
	_lst_delete_node(nodeToDelete);
	lst->size--;
	return data;
}

int lst_at(List lst, size_t position)
{
	if (lst.size <= position)
	{
		return NULL;
	}

	_Node* node = _lst_get_node_forward(lst._start, position);
	return node->data;
}

void lst_print(List lst)
{
	_Node* current = lst._start;

	printf("[");
	while (current->next)
	{
		printf("%d, ", current->data);
		current = _lst_get_node_forward(current, 1);
	}
	printf("%d]", current->data);
}

int lst_front(List lst)
{
	return lst._start->data;
}

int lst_end(List lst)
{
	_Node* lastNode = _lst_get_node_forward(lst._start, lst.size - 1);
	return lastNode->data;
}

size_t lst_size(List lst)
{
	return lst.size;
}


int lst_empty(List lst)
{
	return lst.size == 0;
}

void lst_swap(List* lst, size_t position1, size_t position2)
{
	if (position1 == position2)
	{
		return;
	}

	size_t lowerPos = (position1 <= position2) ? position1 : position2;
	size_t higherPos = (position1 > position2) ? position1 : position2;

	if (lst->size <= higherPos)
	{
		return;
	}

	_Node* prevLowerNode;
	_Node* lowerNode;

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

	_Node* prevHigherNode = _lst_get_node_forward(lowerNode, higherPos - lowerPos - 1);
	_Node* higherNode = prevHigherNode->next;

	if (lowerPos == 0)
	{
		lst->_start = higherNode;
	}
	else
	{
		prevLowerNode->next = higherNode;
	}
	prevHigherNode->next = lowerNode;

	_Node* tempNode = lowerNode->next;
	lowerNode->next = higherNode->next;
	higherNode->next = tempNode;
}
