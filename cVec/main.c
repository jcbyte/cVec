#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int data;
	struct _Node* next;
} _Node;

typedef struct {
	_Node* _start;
	size_t size;
} Vector;

Vector vec_create()
{
	return (Vector) { NULL, 0 };
}

_Node* _vec_create_node(int data)
{
	_Node* node = malloc(sizeof(_Node));
	node->data = data;
	node->next = NULL;
	return node;
}

void _vec_delete_node(_Node* node)
{
	free(node);
}

_Node* _vec_get_node_forward(_Node* node, size_t forward)
{
	_Node* forwardNode = node;
	for (int i = 0; i < forward; i++)
	{
		forwardNode = forwardNode->next;
	}

	return forwardNode;
}

void vec_push_front(Vector* vec, int value)
{
	_Node* newNode = _vec_create_node(value);

	newNode->next = vec->_start;
	vec->_start = newNode;

	vec->size++;
}

void vec_push_back(Vector* vec, int value)
{
	_Node* newNode = _vec_create_node(value);

	if (vec->size == 0)
	{
		vec->_start = newNode;
	}
	else
	{
		_Node* lastNode = _vec_get_node_forward(vec->_start, vec->size - 1);
		lastNode->next = newNode;
	}

	vec->size++;
}

void vec_insert(Vector* vec, int value, size_t position)
{
	if (vec->size < position)
	{
		return;
	}

	_Node* newNode = _vec_create_node(value);

	if (position == 0)
	{
		newNode->next = vec->_start;
		vec->_start = newNode;
	}
	else
	{
		_Node* nodeAt = _vec_get_node_forward(vec->_start, position - 1);
		newNode->next = nodeAt->next;
		nodeAt->next = newNode;
	}

	vec->size++;
}

int vec_pop_front(Vector* vec)
{
	if (vec_empty(*vec))
	{
		return NULL;
	}

	_Node* firstNode = vec->_start;
	vec->_start = firstNode->next;

	int data = firstNode->data;
	_vec_delete_node(firstNode);
	vec->size--;
	return data;
}

int vec_pop_back(Vector* vec)
{
	if (vec_empty(*vec))
	{
		return NULL;
	}

	_Node* prevLastNode = _vec_get_node_forward(vec->_start, vec->size - 1 - 1);
	_Node* lastNode = prevLastNode->next;
	prevLastNode->next = NULL;
	
	int data = lastNode->data;
	_vec_delete_node(lastNode);
	vec->size--;
	return data;
}

int vec_remove(Vector* vec, int value)
{
	_Node* prevNode = NULL;
	_Node* currentNode = vec->_start;

	while (currentNode != NULL)
	{
		if (currentNode->data == value)
		{
			if (prevNode == NULL)
			{
				vec->_start = currentNode->next;
			}
			else
			{
				prevNode->next = currentNode->next;
			}

			int data = currentNode->data;
			_vec_delete_node(currentNode);
			vec->size--;
			return data;			
		}

		prevNode = currentNode;
		currentNode = currentNode->next;
	}
}

int vec_remove_at(Vector* vec, size_t position)
{
	if (vec->size <= position)
	{
		return NULL;
	}

	_Node* nodeToDelete;
	if (position == 0)
	{
		nodeToDelete = vec->_start;
		vec->_start = nodeToDelete->next;
	}
	else
	{
		_Node* prevNode = _vec_get_node_forward(vec->_start, position - 1);
		nodeToDelete = prevNode->next;
		prevNode->next = nodeToDelete->next;
	}

	int data = nodeToDelete->data;
	_vec_delete_node(nodeToDelete);
	vec->size--;
	return data;
}

int vec_at(Vector vec, size_t position)
{
	if (vec.size <= position)
	{
		return NULL;
	}

	_Node* node = _vec_get_node_forward(vec._start, position);
	return node->data;
}

void vec_print(Vector vec)
{
	_Node* current = vec._start;

	printf("[");
	while (current->next)
	{
		printf("%d, ", current->data);
		current = _vec_get_node_forward(current, 1);
	}
	printf("%d]", current->data);
}

int vec_font(Vector vec)
{
	return vec._start->data;
}

int vec_end(Vector vec)
{
	_Node* lastNode = _vec_get_node_forward(vec._start, vec.size - 1);
	return lastNode->data;
}

int vec_empty(Vector vec)
{
	return vec.size == 0;
}

void vec_swap(Vector* vec, size_t position1, size_t position2)
{
	if (position1 == position2)
	{
		return;
	}

	size_t lowerPos = (position1 <= position2) ? position1 : position2;
	size_t higherPos = (position1 > position2) ? position1 : position2;

	if (vec->size <= higherPos)
	{
		return;
	}

	_Node* prevLowerNode;
	_Node* lowerNode;

	if (lowerPos == 0)
	{
		prevLowerNode = NULL;
		lowerNode = vec->_start;
	}
	else
	{
		prevLowerNode = _vec_get_node_forward(vec->_start, lowerPos - 1);
		lowerNode = prevLowerNode->next;
	}

	_Node* prevHigherNode = _vec_get_node_forward(lowerNode, higherPos - lowerPos - 1);
	_Node* higherNode = prevHigherNode->next;

	if (lowerPos == 0)
	{
		vec->_start = higherNode;
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

int main()
{
	Vector vec = vec_create();

	vec_push_back(&vec, 2);
	vec_push_back(&vec, 4);
	vec_push_front(&vec, 1);
	vec_insert(&vec, 3, 2);

	vec_print(vec);
	printf("\n");

	vec_swap(&vec, 2, 1);
	vec_print(vec);

	return 0;
}
