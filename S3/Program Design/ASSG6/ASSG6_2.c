#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;
	struct node *next;
};

typedef struct node *node;

struct queue {
	node head;
	node tail;
};

node Create_Node (int k) {
	node x;
	x = (node) malloc (sizeof (struct node));

	x -> data = k;
	x -> next = NULL;

	return x;
}

void Enqueue (struct queue *Q, node x) {
	if (Q -> head == NULL) {
		Q -> head = Q -> tail = x;
	}

	else {
		Q -> tail -> next = x;
		Q -> tail = x;
	}
}

void Dequeue (struct queue *Q) {
	if (Q -> head == NULL) 
		printf ("-1\n");

	else {
		node x = Q -> head;

		Q -> head = Q -> head -> next;

		printf ("%d\n", x -> data);
		free(x);
	}
}

void Queue_Empty (struct queue *Q) {
	if (Q -> head == NULL)
		printf ("-1\n");
	else
		printf ("1\n");
}

void main () {
	struct queue *Q;
	Q = (struct queue *) malloc (sizeof (struct queue));
	Q -> head = Q -> tail = NULL;

	char ch;
	int k;
	node x;

	while (1) {
		scanf ("%c", &ch);

		switch (ch) {
			case 'i': scanf ("%d", &k);
				  x = Create_Node (k);
				  Enqueue (Q, x);
				  break;

			case 'd': Dequeue (Q);
				  break;

			case 'e': Queue_Empty (Q);
				  break;

			case 't': free (Q);
				  exit(0);
		}
	}
}
