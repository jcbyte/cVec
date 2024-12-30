#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int data;
	struct Node* next;
} Node;

typedef struct {
	Node* start;
	size_t size;
} Vector;

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

void vec_push(Vector* vec, int value)
{
	Node* newNode = _vec_create_node(value);

	if (vec->size == 0)
	{
		vec->start = newNode;
	}
	else
	{
		Node* lastNode = _vec_get_node_forward(vec->start, vec->size - 1);
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
		newNode->next = vec->start;
		vec->start = newNode;
	}
	else
	{
		Node* nodeAt = _vec_get_node_forward(vec->start, position);
		newNode->next = nodeAt->next;
		nodeAt->next = newNode;
	}

	vec->size++;
}

int vec_remove(Vector* vec, int value)
{
	Node* prevNode = NULL;
	Node* iNode = vec->start;
	while (iNode != NULL)
	{
		if (iNode->data == value)
		{
			if (prevNode == NULL)
			{
				vec->start = iNode->next;
			}
			else
			{
				prevNode->next = iNode->next;
			}

			int data = iNode->data;
			_vec_delete_node(iNode);

			vec->size--;
			
			return data;			
		}

		prevNode = iNode;
		iNode = iNode->next;
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
		nodeToDelete = vec->start;
		vec->start = nodeToDelete->next;
	}
	else
	{
		Node* prevNode = _vec_get_node_forward(vec->start, position - 1);
		nodeToDelete = prevNode->next;
		prevNode->next = nodeToDelete->next;
	}

	int data = nodeToDelete->data;
	_vec_delete_node(nodeToDelete);

	vec->size--;

	return data;
}

int main()
{
	Vector vec = { NULL, 0 };

	vec_push(&vec, 20);
	vec_push(&vec, 22);
	vec_push(&vec, 24);

	return 0;
}
