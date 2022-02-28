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

void Insert(struct tree *T, node x) {
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
	else if (x -> key > y -> key)
		y -> right = x;
}

int Height(node x) {
	if (x == NULL)
		return -1;

	int l, r, max;
	l = Height(x -> left);
	r = Height(x -> right);
	max = (l > r) ? l : r;

	return (max + 1);
}

int Is_AVL(node x) {
	if (x != NULL) {
		int l = Height(x -> left);
		int r = Height(x -> right);

		int bf = l - r;

		if ( (bf > 1) || (bf < -1) )
			return 0;
		else {
			if ( Is_AVL(x -> left) && Is_AVL(x -> right) )
				return 1;
			else
				return 0;
		}
	}

	else
		return 1;
}

void main() {
	struct tree *T = (struct tree *) malloc (sizeof (struct tree));
	T -> root = NULL;

	char ch;
	int k;
	node x;

	while (1) {
		scanf("%c", &ch);

		switch (ch) {
			case 'i': scanf (" %d", &k);
				  x = Create_Node(k);
				  Insert(T, x);
				  break;

			case 'c': if ( Is_AVL(T -> root) )
					  printf ("1\n");
				  else
					  printf ("0\n");
				  break;

			case 't': free(T);
				  exit(0);
		}
	}
}
