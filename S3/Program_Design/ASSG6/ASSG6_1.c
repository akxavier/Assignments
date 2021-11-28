#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;
	struct node *next;
};

typedef struct node *node;

struct stack {
	node top;
};

node Create_Node (int k) {
	node x;
	x = (node) malloc (sizeof (struct node));

	x -> data = k;
	x -> next = NULL;

	return x;
}

void Push (struct stack *S, node x) {
	x -> next = S -> top; 
	S -> top = x;
}

void Pop (struct stack *S) {
	node x = S -> top;

	if (x == NULL)
		printf ("-1\n");

	else {
		S -> top = x -> next;

		printf ("%d\n", x -> data);
		free(x);
	}
}

void Stack_Empty (struct stack *S) {
	if (S -> top == NULL)
		printf ("-1\n");
	else
		printf ("1\n");
}

void main () {
	struct stack *S;
	S = (struct stack *) malloc (sizeof (struct stack));
	S -> top = NULL;

	char ch;
	int k;
	node x;

	while (1) {
		scanf ("%c", &ch);

		switch (ch) {
			case 'i': scanf ("%d", &k);
				  x = Create_Node (k);
				  Push (S, x);
				  break;

			case 'd': Pop (S);
				  break;

			case 'e': Stack_Empty (S);
				  break;

			case 't': free (S);
				  exit(0);
		}
	}
}
