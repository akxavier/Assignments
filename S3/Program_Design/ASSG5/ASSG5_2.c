#include <stdio.h>
#include <stdlib.h>

struct node {
	int key;
	struct node *next;
	struct node *prev;
};

typedef struct node *node;

struct LL {
	node head;
};

node CREATE_NODE (int k) {
	node temp;
	temp = (node) malloc (sizeof (struct node));

	temp -> key = k;
	temp -> next = NULL;
	temp -> prev = NULL;
	
	return temp;
}

node LIST_SEARCH (struct LL *L, int k) {
	node present = L -> head;

	while ( (present != NULL) && (present -> key != k) )
		present = present -> next;

	return present;
}

void LIST_INSERT_FRONT (struct LL *L, node x) {
	x -> next = L -> head;

	if (L -> head != NULL)
		L -> head -> prev = x;
	L -> head = x;
}

void LIST_INSERT_TAIL (struct LL *L, node x) {
	node present = L -> head;

	if (L -> head == NULL) 
		L -> head = x;

	else {
		while (present -> next != NULL)
			present = present -> next;

		present -> next = x;
		x -> prev = present;
	}
}

void LIST_INSERT_AFTER (struct LL *L, node x, node y) {
	if (y -> next == NULL) {
		x -> prev = y;
		y -> next = x;
		return;
	}

	y -> next -> prev = x;
	x -> next = y -> next;
	x -> prev = y;
	y -> next = x;
}

void LIST_INSERT_BEFORE (struct LL *L, node x, node y) {
	if (y == L -> head) {
		y -> prev = x;
		x -> next = y;
		L -> head = x;
		return;
	}

	y -> prev -> next = x;
	x -> prev = y -> prev;
	x -> next = y;
	y -> prev = x;
}

void LIST_DELETE (struct LL *L, node x) {
	if (x == L -> head) {
		if (L -> head -> next == NULL) {
			L -> head = NULL;
			printf ("NULL\n");
		}

		else {
			L -> head = L -> head -> next;
			L -> head -> prev = NULL;
			printf ("%d\n", L -> head -> key);
		}
	}

	else if (x -> next == NULL) {
		x -> prev -> next = NULL;
		printf ("NULL\n");
	}

	else {
		x -> prev -> next = x -> next;
		x -> next -> prev = x -> prev;
		printf ("%d\n", x -> next -> key);
	}

	free (x);
}

void LIST_DELETE_INITIAL (struct LL *L) {
	if (L -> head == NULL) {
		printf ("Not Found\n");
		return;
	}

	printf ("%d\n", L -> head -> key);
	node x = L -> head;

	if (L -> head -> next == NULL) 
		L -> head = NULL;
	else {
		L -> head = L -> head -> next;
		L -> head -> prev = NULL;
	}

	free (x);
}

void LIST_DELETE_LAST (struct LL *L) {
	if (L -> head == NULL) {
		printf ("Not Found\n");
		return;
	}

	node present = L -> head;

	if (L -> head -> next == NULL) {
		printf ("%d\n", L -> head -> key);
		L -> head = NULL;
		free (present);
		return;
	}

	while (present -> next != NULL) 
		present = present -> next;

	printf ("%d\n", present -> key);

	present -> prev -> next = NULL;
	free (present);
}

void PRINT_REVERSE (struct LL *L, int k) {
	node x = LIST_SEARCH (L, k);
	if (x == NULL) {
		printf ("Not Found\n");
		return;
	}

	while (x != NULL) {
		printf ("%d ", x -> key);
		x = x -> prev;
	}

	printf ("\n");
}

void main () {
	struct LL *L;
	L = (struct LL *) malloc (sizeof (struct LL));

	char ch;
	int k, l;
	node x, y;

	while (1) {
		scanf ("%c", &ch);

		switch (ch) {
			case 'f': scanf (" %d", &k);
				  x = CREATE_NODE (k);
				  LIST_INSERT_FRONT (L, x);
				  break;

			case 't': scanf (" %d", &k);
				  x = CREATE_NODE (k);
				  LIST_INSERT_TAIL (L, x);
				  break;

			case 'a': scanf (" %d %d", &k, &l);
				  x = CREATE_NODE (k);
				  y = LIST_SEARCH (L, l);
				  LIST_INSERT_AFTER (L, x, y);
				  break;

			case 'b': scanf (" %d %d", &k, &l);
				  x = CREATE_NODE (k);
				  y = LIST_SEARCH (L, l);
				  LIST_INSERT_BEFORE (L, x, y);
				  break;

			case 'd': scanf (" %d", &k);
				  x = LIST_SEARCH (L, k);
				  if (x == NULL)
					  printf ("Not Found\n");
				  else
					  LIST_DELETE (L, x);
				  break;

			case 'i': LIST_DELETE_INITIAL (L);
				  break;

			case 'l': LIST_DELETE_LAST (L);
				  break;

			case 'r': scanf (" %d", &k);
				  PRINT_REVERSE (L, k);
				  break;

			case 'e': free (L);
				  exit (0);
		}
	}
}
