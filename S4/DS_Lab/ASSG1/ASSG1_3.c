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

node Create_Node (int k, node left, node right) {
	node x;
	x = (node) malloc (sizeof (struct node));

	x -> key = k;
	x -> left = left;
	x -> right = right;

	return x;
}

node Build_Tree (char str[], int *i) {
	node left, right, x;
	char substr[10];
	int k;

	if (str[*i] == '(') {
		*i = *i + 2;

		if (str[*i] == ')')
			return NULL;

		int j = 0;
		while (substr[j] != '\0') {
			substr[j] = ' ';
			j++;
		}

		j = 0;
		substr[j] = str[*i];
		while (str[*i + 1] != ' ') {
			*i = *i + 1;
			substr[++j] = str[*i];
		}

		k = atoi (substr);

		*i = *i + 2;

		left = Build_Tree (str, i);

		*i = *i + 2;

		right = Build_Tree (str, i);

		*i = *i + 2;

		if (str[*i] == ')') {
			x = Create_Node (k, left, right);
			return x;
		}
	}
}

void INORDER_TREE_WALK (node x) {
	if (x != NULL) {
		INORDER_TREE_WALK(x -> left);
		printf ("%d ", x -> key);
		INORDER_TREE_WALK(x -> right);
	}
}

int Deletion_BST (node x) {
	if (x == NULL) 
		return 0;

	int l, r;

	if (x -> left == NULL)
		l = 0;
	else if (x -> key < x -> left -> key)
		l = 1;
	else
		l = Deletion_BST (x -> left);

	if (x -> right == NULL)
		r = 0;
	else if (x -> key > x -> right -> key)
		r = 1;
	else
		r = Deletion_BST (x -> right);

	return (l + r);
}

void main () {
	struct tree *T;
	T = (struct tree *) malloc (sizeof (struct tree));

	T -> root = NULL;

	char str[100000];
	int i = 0, n;

	scanf ("%[^\n]", str);

	T -> root = Build_Tree (str, &i);

	//INORDER_TREE_WALK(T -> root);
	
	n = Deletion_BST (T -> root);
	printf ("%d", n);
}
