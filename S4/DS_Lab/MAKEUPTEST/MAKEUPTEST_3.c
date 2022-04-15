/* NOTE
 * This solution is incomplete. 
 * If anyone comes across a complete solution, feel free to create a pull request
 */

#include <stdio.h>
#include <stdlib.h>

struct node {
	int key;
	struct node *p;
	struct node *left;
	struct node *right;
	int stat;
};

typedef struct node *node;

struct tree {
	node root;
};

node Create_Node (int k, node left, node right) {
	node x;
	x = (node) malloc (sizeof (struct node));

	x -> key = k;
	x -> p = NULL;
	x -> left = left;
	x -> right = right;
	x -> stat = 0;

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
			if(left != NULL)
				left -> p = x;
			if(right != NULL)
				right -> p = x;
			return x;
		}
	}
}

void Check_To_Include(node x) {
	if(x == NULL)
		return;

	if(x -> p != NULL) {
		if(x->p->stat == 1) {
			x->stat = 0;
			if(x->left != NULL)
				x->left->stat = 1;
			if(x->right != NULL)
				x->right->stat = 1;

			Check_To_Include(x->left);
			Check_To_Include(x->right);
		}

		else if(x->p->stat == 0) {
			if(x->key < ((x->left == NULL) ? 0 : x->left->key) + ((x->right == NULL) ? 0 : x->right->key)) {
				x->stat = 0;
				if(x->left != NULL)
					x->left->stat = 1;
				if(x->right != NULL)
					x->right->stat = 1;

				Check_To_Include(x->left);
				Check_To_Include(x->right);
			}

			else {
				x->stat = 1;
				
				Check_To_Include(x->left);
				Check_To_Include(x->right);
			}
		}
	}

	else {
		if(x->key < ((x->left == NULL) ? 0 : x->left->key) + ((x->right == NULL) ? 0 : x->right->key)) {
			x->stat = 0;
			if(x->left != NULL)
				x->left->stat = 1;
			if(x->right != NULL)
				x->right->stat = 1;

			Check_To_Include(x->left);
			Check_To_Include(x->right);
		}

		else {
			x->stat = 1;

			Check_To_Include(x->left);
			Check_To_Include(x->right);
		}
	}
}

int Get_Sum(node x) {
	if(x == NULL)
		return 0;

	int this;

	if(x->stat == 1)
		this = x->key;
	else
		this = 0;

	return (this + Get_Sum(x->left) + Get_Sum(x->right));
}

int Get_Max_Sum(node x) {
	Check_To_Include(x);

	return Get_Sum(x);
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
	
	int sum = Get_Max_Sum(T -> root);
	printf ("%d", sum);
}

/* NOTE
 * This solution is incomplete. 
 * If anyone comes across a complete solution, feel free to create a pull request
 */
