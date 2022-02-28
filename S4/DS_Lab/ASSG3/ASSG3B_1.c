#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
	int key;
	char color[2];
	struct node *p;
	struct node *left;
	struct node *right;
};

typedef struct node *node;

struct tree {
	node root;
	node nil;
};

node Create_Node(int key) {
	node x = (node) malloc (sizeof( struct node ));
	x -> key = key;

	return x;
}

void Left_Rotate(struct tree *T, node x) {
	node y = x -> right;
	x -> right = y -> left;

	if (y -> left != T -> nil) {
		y -> left ->  p = x;
	}
	y -> p = x -> p;

	if (x -> p == T -> nil) {
		T -> root = y;
	}

	else if (x == x -> p -> left) {
		x -> p -> left = y;
	}

	else {
		x -> p -> right = y;
	}

	y -> left = x;
	x -> p = y;
}

void Right_Rotate(struct tree *T, node x) {
        node y = x -> left;
        x -> left = y -> right;

        if (y -> right != T -> nil) {
                y -> right ->  p = x;
        }
        y -> p = x -> p;

        if (x -> p == T -> nil) {
                T -> root = y;
        }

        else if (x == x -> p -> right) {
                x -> p -> right = y;
        }

        else {
                x -> p -> left = y;
        }

        y -> right = x;
        x -> p = y;
}

void RB_Insert_Fixup(struct tree *T, node z) {
	while ( strcmp(z -> p -> color, "R") == 0 ) {
		if (z -> p == z -> p -> p -> left) {
			node y = z -> p -> p -> right;

			if ( strcmp(y -> color, "R") == 0 ) {
				strcpy(z -> p -> color, "B");
				strcpy(y -> color, "B");
				strcpy(z -> p -> p -> color, "R");
				z = z -> p -> p;
			}

			else {
				if (z == z -> p -> right) {
					z = z -> p;
					Left_Rotate(T, z);
				}

				strcpy(z -> p -> color, "B");
				strcpy(z -> p -> p -> color, "R");
				Right_Rotate(T, z -> p -> p);
			}
		}

		else {
			node y = z -> p -> p -> left;

                        if ( strcmp(y -> color, "R") == 0 ) {
                                strcpy(z -> p -> color, "B");
                                strcpy(y -> color, "B");
                                strcpy(z -> p -> p -> color, "R");
                                z = z -> p -> p;
                        }

                        else {
                                if (z == z -> p -> left) {
                                        z = z -> p;
                                        Right_Rotate(T, z);
                                }

                                strcpy(z -> p -> color, "B");
                                strcpy(z -> p -> p -> color, "R");
                                Left_Rotate(T, z -> p -> p);
                        }
		}
	}

	strcpy(T -> root -> color, "B");
}

void Print_Tree (struct tree *T, node x) {
	if (x == T -> nil)
		printf ("( ) ");

	else {
		printf ("( ");

		printf ("%d %s ", x -> key, x -> color);
		Print_Tree (T, x -> left);
		Print_Tree (T, x -> right);

		printf (") ");
	}
}

void Insert_Red_Black(struct tree *T, int key) {
	node x, y, z;
	z = Create_Node(key);

	y = T -> nil;
	x = T -> root;

	while (x != T -> nil) {
		y = x;

		if (z -> key < x -> key)
			x = x -> left;
		else
			x = x -> right;
	}

	z -> p = y;

	if (y == T -> nil) {
		T -> root = z;
	}
	else if (z -> key < y -> key) {
		y -> left = z;
	}
	else {
		y -> right = z;
	}

	z -> left = T -> nil;
	z -> right = T -> nil;
	strcpy(z -> color, "R");

	RB_Insert_Fixup(T, z);

	Print_Tree(T, T -> root);
	printf ("\n");
}

void main() {
	struct tree *T;
	T = (struct tree *) malloc (sizeof(struct tree));

	T -> nil = (node) malloc (sizeof(struct node));

	strcpy(T -> nil -> color, "B");
	T -> nil -> p = T -> nil -> left = T -> nil -> right = NULL;

	T -> root = T -> nil;

	char str[10];
	
	scanf ("%s", str);

	while ( strcmp(str, "t") != 0 ) {
		int k = atoi(str);
	
		Insert_Red_Black(T, k);

		scanf ("%s", str);
	}

	free(T);
	exit(0);
}



