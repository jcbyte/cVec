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

void vec_push(Vector* vec, int value)
{
	Node* newNode = _vec_create_node(value);

	if (vec->size == 0)
	{
		vec->start = newNode;
	}
	else
	{
		Node* iNode = vec->start;
		while (iNode->next != NULL)
		{
			iNode = iNode->next;
		}
		iNode->next = newNode;
	}

	vec->size++;
}

void vec_insert(Vector vec, int value, size_t position)
{

}

void vec_remove(Vector vec, int value)
{

}

void vec_remove_at(Vector vec, size_t position)
{

}

int main()
{
	Vector vec = { NULL, 0 };

	vec_push(&vec, 20);
	vec_push(&vec, 22);
	vec_push(&vec, 24);

	return 0;
}
