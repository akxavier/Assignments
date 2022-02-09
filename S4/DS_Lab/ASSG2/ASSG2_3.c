#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
	char *first;
	char *last;
	int age;
	struct node *p;
	struct node *left;
	struct node *right;
};

typedef struct node *node;

struct tree {
	node root;
};

struct tree *T[128];

node Create_Node () {
	node x = (node) malloc (sizeof (struct node));
	x -> p = x -> left = x -> right = NULL;

	return x;
}

void Insert (struct tree *T, node x) {
	node y, z;
	y = NULL;
	z = T -> root;

	while (z != NULL) {
		y = z;

		if (x -> age < z -> age)
			z = z -> left;
		else
			z = z -> right;
	}

	if (y == NULL)
		T -> root = x;
	else if (x -> age < y -> age)
		y -> left = x;
	else
		y -> right = x;

	x -> p = y;
}

int Hash (node x) {
	printf ("Before strlen\n");
	//int len = strlen (x -> last);
	int len = 0;
	for (int i = 0; x -> last[i] != '\0'; i++)
		len++;

	int sum = 0;
	printf ("After strlen\n");

	for (int i = 0; i < len; i++) {
		sum += (int) x -> last[i];
	}

	return (sum % 128);
}

void Insert_Data (node x) {
	int pos = Hash (x);

	printf ("Before Insert\n");
	Insert (T[pos], x);
}

void main () {
	char ch;
	char *first, *last;
	int age;
	node x;

	for (int i = 0; i < 128; i++) {
		T[i] = (struct tree *) malloc (sizeof (struct tree));
		T[i] -> root = NULL;
	}
	
	while (1) {
		scanf ("%c", &ch);

		switch (ch) {
			case 'i': x = Create_Node();
				  scanf ("%s", x -> first);
				  scanf ("%s", x -> last);
				  scanf ("%d", x -> age);
				  printf ("%s\n%s\n%d\n", x -> first, x -> last, x -> age);
				  Insert_Data(x);
				  break;

			case 'p': exit(0);
		}
	}
}
