#include <stdio.h>
#include <stdlib.h>

struct node {
	int key;
	int height;
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
	x -> height = 0;

	return x;
}

int Height(node x) {
	if (x == NULL)
		return -1;

	int l = Height(x -> left);
	int r = Height(x -> right);

	int max = (l > r) ? l : r;

	return (max + 1);
}

int Get_Balance(node x) {
	return ( Height(x -> left) - Height(x -> right) );
}

node Search(struct tree *T, int k) {
        node x = T -> root;

        while ( (x != NULL) && (x -> key != k) ) {
                        if (k < x -> key) 
				x = x -> left;
			else
				x = x -> right;
	}

	return x;
}

void Left_Rotate(struct tree *T, node z) {
	node y = z -> right;

	z -> right = y -> left;
	if (y -> left != NULL) {
		y -> left -> p = z;
	}

	y -> left = z;
	y -> p = z -> p;
	
	if (z -> p == NULL) 
		T -> root = y;
	else if (z == z -> p -> left)
		z -> p -> left = y;
	else if (z == z -> p -> right)
		z -> p -> right = y;

	z -> p = y;

	// Update height of z and y
	z -> height = Height(z);
	y -> height = Height(y);
}

void Right_Rotate(struct tree *T, node z) {
        node y = z -> left;

        z -> left = y -> right;
        if (y -> right != NULL) {
                y -> right -> p = z;
        }

        y -> right = z;
        y -> p = z -> p;

        if (z -> p == NULL)
                T -> root = y;
        else if (z == z -> p -> left)
                z -> p -> left = y;
        else if (z == z -> p -> right)
                z -> p -> right = y;

        z -> p = y;

        // Update height of z and y
        z -> height = Height(z);
        y -> height = Height(y);
}


void Insert_Node(struct tree *T, node z) {
        node y = NULL;
        node temp = T -> root;

        while (temp != NULL) {
                y = temp;

                if (z -> key < temp -> key)
                        temp = temp -> left;
                else
                        temp = temp -> right;
        }

        z -> p = y;

        if (y == NULL)
                T -> root = z;
        else if (z -> key < y -> key)
                y -> left = z;
        else
                y -> right = z;

        while (y != NULL) {
		//printf("Inside while\n");
                node x = y -> p;

		y -> height = Height(y);

		if (x != NULL) {
			int balance = Get_Balance(x);

			if (balance < -1 || balance > 1) {
				if (y == x -> left) {
					if (z == x -> left -> left) {
						Right_Rotate(T, x);
					}

					else if (z == x -> left -> right) {
						Left_Rotate(T, y);
						Right_Rotate(T, x);
					}
				}

				else if (y == x -> right) {
					if (z == x -> right -> right) {
						Left_Rotate(T, x);
					}

					else if (z == x -> right -> left) {
						Right_Rotate(T, y);
						Left_Rotate(T, x);
					}
				}
			}
		}
		z = z -> p;
		y = z -> p;
	}
}

void Insert(struct tree *T, int k) {
	node x = Create_Node(k);

	Insert_Node(T, x);
}

node Tree_Maximum(node x) {
	while (x -> right != NULL)
		x = x -> right;

	return x;
}

void Transplant(struct tree *T, node u, node v) {
	if (u -> p == NULL)
		T -> root = v;
	else if (u == u -> p -> left)
		u -> p -> left = v;
	else
		u -> p -> right = v;

	if (v != NULL) 
		v -> p = u -> p;
}

void Delete_Node(struct tree *T, int k) {
	node z = Search(T, k);

	if (z == NULL) {
		printf("FALSE\n");
		return;
	}

	node y = z -> p;

	if (z -> left == NULL) 
		Transplant(T, z, z -> right);
	else if (z -> right == NULL)
		Transplant(T, z, z -> left);
	else {
		y = Tree_Maximum(z -> left);
		if (y -> p != z) {
			Transplant(T, y, y -> left);
			y -> left = z -> left;
			y -> left -> p = y;
		}
		Transplant(T, z, y);
		y -> right = z -> right;
		y -> right -> p = y;
	}

	printf("%d\n", z -> key);
	free(z);

	if ((y != NULL) && (y -> p != NULL) && (Get_Balance(y -> p) < -1))
		Left_Rotate(T, y -> p);

	while (y != NULL) {
		y -> height = Height(y);

		node x = y -> p;

		if (x != NULL) {
			int balance = Get_Balance(x);

			if (balance < -1) {
				if ((x -> right != NULL) && (Get_Balance(x -> right) <= 0))
					Left_Rotate(T, x);
				else if (x -> right != NULL) {
					Right_Rotate(T, x -> right);
					Left_Rotate(T, x);
				}
			}
		}

		y = y -> p;
	}
}

void Print_Tree(node x) {
	if (x == NULL) {
		printf ("( ) ");
	}

	else {
		printf ("( ");

		printf ("%d ", x -> key);
		Print_Tree(x -> left);
		Print_Tree(x -> right);

		printf (") ");
	}
}

void main() {
	struct tree *T = (struct tree *) malloc (sizeof (struct tree));
	T -> root = NULL;

	char ch;
	node x;
	int k;

	while(1) {
		scanf("%c", &ch);

		switch (ch) {
			case 'i': scanf("%d", &k);
				  Insert(T, k);
				  break;

			case 'd': scanf("%d", &k);
				  Delete_Node(T, k);
				  break;

			case 's': scanf("%d", &k);
				  if ( Search(T, k) != NULL ) 
					  printf("TRUE\n");
				  else
					  printf("FALSE\n");
				  break;

			case 'b': scanf("%d", &k);
				  x = Search(T, k);
				  if (x != NULL)
					  printf("%d\n", Get_Balance(x));
				  else
					  printf("FALSE\n");
				  break;

			case 'p': Print_Tree(T -> root);
				  printf("\n");
				  break;

			case 'e': free(T);
				  exit(0);
				  break;
		}
	}
}


