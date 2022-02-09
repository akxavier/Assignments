#include <stdio.h>
#include <stdlib.h>

struct node {
	int key;
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
	x -> left = x -> right = NULL;

	return x;
}

int Get_Height (struct tree *T) {
	int h = -1;
	node x = T -> root;

	while (x != NULL) {
		h++;
		x = x -> left;
	}

	return h;
}

node Find_Node (node root, int d) {
	if (root == NULL)
		return NULL;

	if (d == 0) {
		if ( (root -> left == NULL) || (root -> right == NULL) ) 
			return root;

		else 
			return NULL;
	}

	else if (d > 0) {
		if ( Find_Node(root -> left, d - 1) != NULL )
			return Find_Node(root -> left, d - 1);
		else if ( Find_Node(root -> right, d - 1) != NULL)
			return Find_Node(root -> right, d - 1);
	}
}

node Locate (struct tree *T) {
	int h = Get_Height (T);
	node x;

	int i = 0;

	do {
		x = Find_Node (T -> root, i);
		i++;
	} while ( (x == NULL) && (i <= h) );

	return x;
}

void Insert (struct tree *T, int k) {
	node x, y;

	x = Create_Node (k);
	y = Locate (T);

	if (y == NULL) {
		T -> root = x;
		return;
	}

	if (y -> left == NULL)
		y -> left = x;
	else if (y -> right == NULL)
		y -> right = x;
}

void Print (node x) {
	if (x == NULL)
		printf ("( ) ");

	else {
		printf ("( ");

		printf ("%d ", x -> key);
		Print (x -> left);
		Print (x -> right);

		printf (") ");
	}
}

void main () {
	struct tree *T;
	T = (struct tree *) malloc (sizeof (struct tree));

	char ch;
	int k;

	while (1) {
		scanf ("%c", &ch);

		switch (ch) {
			case 'i': scanf ("%d", &k);
				  Insert (T, k);
				  break;

			case 'p': Print (T -> root);
				  printf ("\n");
				  break;

			case 'e': free (T);
				  exit(0);
				  break;
		}
	}
}
