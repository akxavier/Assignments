#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
	int key;
	char color[2];
	char t_id[100];
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

void Insert_Red_Black(char *task_id, int key, struct tree *T) {
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
	strcpy(z -> t_id, task_id);
	RB_Insert_Fixup(T, z);

	Print_Tree(T, T -> root);
	printf ("\n");
}

void main() {
	struct tree *A1;
	A1 = (struct tree *) malloc (sizeof(struct tree));

	A1 -> nil = (node) malloc (sizeof(struct node));

	strcpy(A1 -> nil -> color, "B");
	A1 -> nil -> p = A1 -> nil -> left = A1 -> nil -> right = NULL;

	A1 -> root = A1 -> nil;

	struct tree *A2;
	A2 = (struct tree *) malloc (sizeof(struct tree));

	A2 -> nil = (node) malloc (sizeof(struct node));

	strcpy(A2 -> nil -> color, "B");
	A2 -> nil -> p = A2 -> nil -> left = A2 -> nil -> right = NULL;

	A2 -> root = A2 -> nil;

	char ch, task_id[100];
	int time, app_no, k;

	while(1) {
		scanf("%c", &ch);

		switch(ch) {
			case 'i': scanf(" %s %d %d", task_id, &time, &app_no);
				  if (app_no == 1)
				  	Insert_Task(task_id, time, A1);
				  else
					Insert_Task(task_id, time, A2);
				  break;

			/*case 'a': scanf("%d", &k);
				  if (k == 1)
				  	printf("%d\n", Fairness_Factor(A1));
				  else
					printf("%d\n", Fairness_Factor(A2));
				  break;*/
			case 't': free(A1);
				  free(A2);
				  break;
		}
	}
}
			

