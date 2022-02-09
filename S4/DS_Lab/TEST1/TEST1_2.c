#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
	int r;
	char E_id[100];
	struct node *left;
	struct node *right;
};

typedef struct node *node;

struct tree {
	node root;
};

node Create_Node (char *eid, int r, node left, node right) {
	node x;
	x = (node) malloc (sizeof (struct node));

	strcpy (x -> E_id, eid);
	x -> r = r;
	x -> left = left;
	x -> right = right;

	return x;
}

node Build_Tree (char str[], int *i) {
	node left, right, x;
	char substr[100];
	int r;
	char eid[100];

	if (str[*i] == '(') {
		*i = *i + 2;

		if (str[*i] == ')')
			return NULL;

		int j = 0;
		while (substr[j] != '\0') {
			substr[j] = '\0';
			j++;
		}


		j = 0;
		substr[j] = str[*i];
		while (str[*i + 1] != ' ') {
			*i = *i + 1;
			substr[++j] = str[*i];
		}

		strcpy (eid, substr);

		*i = *i + 2;

		j = 0;
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

		r = atoi (substr);

		*i = *i + 2;

		left = Build_Tree (str, i);

		*i = *i + 2;

		right = Build_Tree (str, i);

		*i = *i + 2;

		if (str[*i] == ')') {
			x = Create_Node (eid, r, left, right);
			return x;
		}
	}
}

void Read_and_Store (struct tree *T) {
	char str[1000000];
        int i = 0;
        
        scanf ("%[^\n]", str);

	T -> root = Build_Tree (str, &i);

}

void Inorder_Tree_Walk (node x) {
	if (x != NULL) {
		Inorder_Tree_Walk(x -> left);
		printf ("%s ", x -> E_id);
		Inorder_Tree_Walk(x -> right);
	}
}

void Print_Employees (struct tree *T) {
	Inorder_Tree_Walk (T -> root);
	printf ("\n");
}

int Calc_Sum (node x) {
	int l, r;

	if ( x == NULL) {
		return 0;
	}

	l = Calc_Sum (x -> left);
	r = Calc_Sum (x -> right);

	return (x -> r + l + r);
}

void Find_Employees (node x) {
	if (x == NULL)
		return;

	if ( (x -> left == NULL) && (x -> right == NULL) ) {
		return;
	}

	Find_Employees (x -> left);
	Find_Employees (x -> right);

	if ( (x -> left == NULL) && (x -> right == NULL) )
		return;

	int lsum, rsum;
	lsum = Calc_Sum (x -> left);
	rsum = Calc_Sum (x -> right);

	if (x -> r > lsum + rsum)
		printf ("%s ", x -> E_id);
}

void main () {
	struct tree *T;
	T = (struct tree *) malloc (sizeof (struct tree));

	T -> root = NULL;

	Read_and_Store (T);

	Print_Employees(T);

	Find_Employees(T -> root);
	printf ("\n");

	free(T);
}
