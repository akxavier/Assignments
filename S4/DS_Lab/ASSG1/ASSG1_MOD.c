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

int Get_Height (node x) {
	if (x == NULL)
		return 0;

	int lh, rh;

	else {
		lh = Get_Height (x -> left);
		rh = Get_Height (x -> right);

		if (lh > rh)
			return (lh + 1);
		else
			return (rh + 1);
    }
}

int Level_Sum (node root, int d) {
	if (root == NULL)
		return 0;

	if (d == 0) {
		return root -> key;
	}

	else if (d > 0) {
		return Level_Sum (root -> left, d - 1) + Level_Sum (root -> right, d - 1);
	}
}

void Calc_Sum (struct tree *T, node x, int k) {
	int sum = 0;

	int i = 0;
	int h = Get_Height (T -> root);

	do {
		sum = sum + Level_Sum (T -> root, i);
		i++;
	} while (i <= h);

	printf ("%d", sum);
}

void main () {
	struct tree *T;
	T = (struct tree *) malloc (sizeof (struct node));

	char str[1000000];
	int id, k;
	node x;

	scanf ("%[^\n]", str);
	scanf ("%d %d", &id, &k);

	T = Build_Tree (str);

	x = Search (T, id);

	Calc_Sum (T, x, k);
}
