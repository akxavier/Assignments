#include <stdio.h>
#include <stdlib.h>

struct node {
	int key;
	struct node *p;
	struct node *left;
	struct node *right;
};

typedef struct node *node;

struct tree {
	node root;
};

node Create_Node (int k) {
	node x = (node) malloc (sizeof (struct node));
	x -> key = k;
	x -> p = x -> left = x -> right = NULL;
	
	return x;
}

void Insert (struct tree *T, node x) {
	node y, z;
	y = NULL;
	z = T -> root;

	while (z != NULL) {
		y = z;
		
		if (x -> key < z -> key)
			z = z -> left;
		else 
			z = z -> right;
	}

	if (y == NULL)
		T -> root = x;
	else if (x -> key < y -> key)
		y -> left = x;
	else 
		y -> right = x;

	x -> p = y;
}

void Transplant (struct tree *T, node u, node v) {
	if (u -> p == NULL)
		T -> root = v;

	else if (u == u -> p -> left)
		u -> p -> left = v;

	else if (u == u -> p -> right)
		u -> p -> right = v;

	if (v != NULL)
		v -> p = u -> p;
}

node Tree_Min (node x) {
	while (x -> left != NULL)
		x = x -> left;
	return x;
}

node Tree_Max (node x) {
	while (x -> right != NULL)
		x = x -> right;
	return x;
}

void Delete (struct tree *T, node x) {
	node y;

	if (x -> right == NULL)
		Transplant (T, x, x -> left);

	else if (x -> left == NULL)
		Transplant (T, x, x -> right);

	else {
		y = Tree_Min (x -> right);

		if (y -> p != x) {
			Transplant (T, y, y -> right);

			x -> right -> p = y;
			y -> right = x -> right;
		}

		Transplant (T, x, y);

		y -> left = x -> left;
		y -> left -> p = y;
	}

	printf ("%d\n", x -> key);
	free (x);
}

node Search (struct tree *T, int k) {
	node x = T -> root;

	while ( (x != NULL) && (x -> key != k) ) {
		if (k < x -> key)
			x = x -> left;
		else
			x = x -> right;
	}

	return x;
}

void Successor (node x) {
	node y;

	if (x -> right != NULL)
		y = Tree_Min (x -> right);

	else {
		y = x -> p;

		while ( (y != NULL) && (x == y -> right) ) {
			x = y;
			y = y -> p;
		}
	}

	if (y == NULL)
		printf ("-1\n");
	else
		printf ("%d\n", y -> key);
}

void Predecessor (node x) {
	node y;

	if (x -> left != NULL)
		y = Tree_Max (x -> left);

	else {
		y = x -> p;

		while ( (y != NULL) && (x == y -> left) ) {
			x = y;
			y = y -> p;
		}
	}

	if (y == NULL)
		printf ("-1\n");
	else 
		printf ("%d\n", y -> key);
}

void Inorder (node x) {
	if (x != NULL) {
		Inorder (x -> left);
		printf ("%d ", x -> key);
		Inorder (x -> right);
	}
}

void Preorder (node x) {
	if (x != NULL) {
		printf ("%d ", x -> key);
		Preorder (x -> left);
		Preorder (x -> right);
	}
}

void Postorder (node x) {
	if (x != NULL) {
		Postorder (x -> left);
		Postorder (x -> right);
		printf ("%d ", x -> key);
	}
}

void main () {
	struct tree *T;
	T = (struct tree *) malloc (sizeof (struct tree));

	char ch;
	int k;
	node x;

	while (1) {
		scanf ("%c ", &ch);

		switch (ch) {
			case 'a': scanf ("%d", &k);
				  x = Create_Node (k);
				  Insert (T, x);
				  break;

			case 'd': scanf ("%d", &k);

				  x = Search (T, k);

				  if (x == NULL)
					  printf ("-1\n");
				  else
					  Delete (T, x);
				  break;

			case 's': scanf ("%d", &k);

				  x = Search (T, k);

				  if (x == NULL)
					  printf ("-1\n");
				  else
					  printf ("1\n");
				  break;

			case 'c': scanf ("%d", &k);

				  x = Search (T, k);
				  Successor (x);
				  break;

			case 'r': scanf ("%d", &k);

				  x = Search (T, k);
				  Predecessor (x);
				  break;

			case 'i': Inorder (T -> root);
				  printf ("\n");
				  break;

			case 'p': Preorder (T -> root);
				  printf ("\n");
				  break;

			case 't': Postorder (T -> root);
				  printf ("\n");
				  break;

			case 'e': free (T);
				  exit (0);
				  break;
		}
	}
}
