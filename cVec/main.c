#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int data;
	struct Node* next;
} Node;

typedef struct {
	Node* _start;
	size_t size;
} Vector;

Vector vec_create()
{
	return (Vector) { NULL, 0 };
}

Node* _vec_create_node(int data)
{
	Node* node = malloc(sizeof(Node));
	node->data = data;
	node->next = NULL;
	return node;
}

void _vec_delete_node(Node* node)
{
	free(node);
}

Node* _vec_get_node_forward(Node* node, size_t forward)
{
	Node* forwardNode = node;
	for (int i = 0; i < forward; i++)
	{
		forwardNode = forwardNode->next;
	}

	return forwardNode;
}

void vec_push_front(Vector* vec, int value)
{
	Node* newNode = _vec_create_node(value);

	newNode->next = vec->_start;
	vec->_start = newNode;

	vec->size++;
}

void vec_push_back(Vector* vec, int value)
{
	Node* newNode = _vec_create_node(value);

	if (vec->size == 0)
	{
		vec->_start = newNode;
	}
	else
	{
		Node* lastNode = _vec_get_node_forward(vec->_start, vec->size - 1);
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

	Node* newNode = _vec_create_node(value);

	if (position == 0)
	{
		newNode->next = vec->_start;
		vec->_start = newNode;
	}
	else
	{
		Node* nodeAt = _vec_get_node_forward(vec->_start, position - 1);
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

	Node* firstNode = vec->_start;
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

	Node* prevLastNode = _vec_get_node_forward(vec->_start, vec->size - 1 - 1);
	Node* lastNode = prevLastNode->next;
	prevLastNode->next = NULL;
	
	int data = lastNode->data;
	_vec_delete_node(lastNode);
	vec->size--;
	return data;
}

int vec_remove(Vector* vec, int value)
{
	Node* prevNode = NULL;
	Node* currentNode = vec->_start;

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

	Node* nodeToDelete;
	if (position == 0)
	{
		nodeToDelete = vec->_start;
		vec->_start = nodeToDelete->next;
	}
	else
	{
		Node* prevNode = _vec_get_node_forward(vec->_start, position - 1);
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

	Node* node = _vec_get_node_forward(vec._start, position);
	return node->data;
}

void vec_print(Vector vec)
{
	Node* current = vec._start;

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
	Node* lastNode = _vec_get_node_forward(vec._start, vec.size - 1);
	return lastNode->data;
}

int vec_empty(Vector vec)
{
	return vec.size == 0;
}

// swap

int main()
{
	Vector vec = vec_create();

	vec_push_back(&vec, 20);
	vec_push_back(&vec, 22);
	vec_push_front(&vec, 24);
	vec_insert(&vec, 3, 2);

	vec_print(vec);

	return 0;
}
