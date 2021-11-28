#include <stdio.h>
#include <stdlib.h>

struct node {
	char data;
	struct node *left;
	struct node *right;
	struct node *next;
};

typedef struct node *node;

struct tree {
	node root;
};

node Create_Node (char k) {
	node x = (node) malloc (sizeof (struct node));

	x -> data = k;
	x -> left = x -> right = x -> next = NULL;

	return x;
}

void Push (struct tree *T, node x) {
	x -> next = T -> root;
	T -> root = x;
}

node Pop (struct tree *T) {
	node x = T -> root;

	T -> root = x -> next;
	return x;
}

node Construct_Tree (struct tree *T, char e[]) {
	node rchild, lchild, x;

	for (int i = 0; e[i] != '\0'; i++) {
		switch (e[i]) {
			case '*':
			case '/':
			case '+':
			case '-': rchild = Pop (T);
				  lchild = Pop (T);

				  x = Create_Node (e[i]);
				  x -> left = lchild;
				  x -> right = rchild;

				  Push (T, x);
				  break;

			default: x = Create_Node (e[i]);
				 Push (T, x);
				 break;
		}
	}
	return T -> root;
}

void Inorder (node x) {
	if (x != NULL) {
		Inorder (x -> left);
		printf ("%c", x -> data);
		Inorder (x -> right);
	}
}

void Preorder (node x) {
	if (x != NULL) {
		printf ("%c", x -> data);
		Preorder (x -> left);
		Preorder (x -> right);
	}
}

void Postorder (node x) {
	if (x != NULL) {
		Postorder (x -> left);
		Postorder (x -> right);
		printf ("%c", x -> data);
	}
}

void main () {
	struct tree *T;
	T = (struct tree *) malloc (sizeof (struct tree));
	T -> root = NULL;

	char ch, e[500];

	while (1) {
		scanf ("%c", &ch);

		switch (ch) {
			case 'e': scanf ("%s", e);
				  T -> root = Construct_Tree (T, e);
				  break;

			case 'i': Inorder (T -> root);
				  printf ("\n");
				  break;

			case 'p': Preorder (T -> root);
				  printf ("\n");
				  break;

			case 's': Postorder (T -> root);
				  printf ("\n");
				  break;

			case 't': free (T);
				  exit(0);
				  break;
		}
	}
}
