#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

		k = atoi(substr);

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

bool Is_Present (node x, int k) {
	if (x == NULL)
		return false;
	else if (x -> key == k)
		return true;
	else 
		return ( Is_Present(x -> left, k) || Is_Present(x -> right, k) );
}

node Find_LCA (node x, int m, int n) {
	if (x == NULL)
		return NULL;

	if ( (x -> key == m) || (x -> key == n) )
		return x;

	if ( Is_Present(x -> left, m) && Is_Present(x -> left, n) )
		return Find_LCA(x -> left, m, n);

	else if ( Is_Present(x -> right, m) && Is_Present(x -> right, n) )
		return Find_LCA(x -> right, m, n);
	else
		return x;
}

void main () {
	struct tree *T;
	T = (struct tree *) malloc (sizeof (struct tree));
	T -> root = NULL;

	char str[1000000];
	int m, n, i = 0;
	node x;

	scanf ("%[^\n]", str);
	scanf ("%d %d", &m, &n);

	T -> root = Build_Tree (str, &i);

	x = Find_LCA (T -> root, m, n);
	printf ("%d", x -> key);
}
