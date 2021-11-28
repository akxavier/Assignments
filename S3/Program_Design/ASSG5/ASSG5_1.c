#include <stdio.h>
#include <stdlib.h>

struct node {
	char key;
	struct node *next;
};

typedef struct node *node;

struct LL {
	node head;
};

node CREATE_NODE (char k) {
	node temp;
	temp = (node) malloc( sizeof( struct node ) );

	temp -> key = k;
	temp -> next = NULL;
	return temp;
}

node LIST_SEARCH (struct LL *L, char k) {
	node present = L -> head;

	while ( (present != NULL) && (present -> key != k) )
		present = present -> next;

	return present;
}

void LIST_INSERT_TAIL (struct LL *L, node x) {
	node present = L -> head;

	if (present == NULL)
		L -> head = x;
	else {
		while (present -> next != NULL)
			present = present -> next;
		present -> next = x;
	}
}

void LIST_INSERT_FRONT (struct LL *L, node x) {
	x -> next = L -> head;
	L -> head = x;
}

void LIST_INSERT_BEFORE (struct LL *L, node x, node y) {
	node present = L -> head;

	while (present -> next != y)
		present = present -> next;

	present -> next = x;
	x -> next = y;
}

void LIST_INSERT_AFTER (struct LL *L, node x, node y) {
	x -> next = y -> next;
	y -> next = x;
}

void LIST_DELETE (struct LL *L, node x) {
	node present = L -> head;

	if (L -> head == x) {
		L -> head = L -> head -> next;
		free (x);

		if (L -> head == NULL) {
			printf ("-2\n");
			return;
		}
		
		else 
			printf ("%c\n", L -> head -> key);
	}

	else {
		while (present -> next != x)
			present = present -> next;

		present -> next = x -> next;
		free (x);

		if (present -> next == NULL)
			printf ("-2\n");
		else 
			printf ("%c\n", present -> next -> key);
	}
}

void LIST_DELETE_FIRST (struct LL *L) {
	if (L -> head == NULL) {
		printf ("-1\n");
		return;
	}

	node present = L -> head;
	printf ("%c\n", present -> key);

	L -> head = L -> head -> next;
	free (present);
}

void LIST_DELETE_LAST (struct LL *L) {
	if (L -> head == NULL) {
		printf ("-1\n");
		return;
	}

	node present = L -> head;
	node previous = NULL;

	while (present -> next != NULL) {
		previous = present;
		present = present -> next;
	}

	printf ("%c\n", present -> key);

	if (previous == NULL)
		L -> head = NULL;
	else
		previous -> next = NULL;

	free (present);
}

void PRINT_LIST (struct LL *L) {
	node present = L -> head;

	if (present == NULL) {
		printf ("NULL\n");
		return;
	}

	while (present != NULL) {
		printf ("%c ", present -> key);
		present = present -> next;
	}
	printf ("\n");
}

void main () {
	node x, y;
	char ch, k, l;
	struct LL *L;

	L = (struct LL *) malloc( sizeof (struct LL) );
	L -> head = NULL;

	while (1) {
		scanf (" %c", &ch);

		switch (ch) {
			case 'f': scanf (" %c", &k);
				  x = CREATE_NODE (k);
				  LIST_INSERT_FRONT (L, x);
				  break;

			case 't': scanf (" %c", &k);
                                  x = CREATE_NODE (k);
                                  LIST_INSERT_TAIL (L, x);
                                  break;

			case 'a': scanf (" %c %c", &k, &l);
				  x = CREATE_NODE (k);
				  y = LIST_SEARCH (L, l);
				  LIST_INSERT_AFTER (L, x, y);
				  break;

			case 'b': scanf (" %c %c", &k, &l);
                                  x = CREATE_NODE (k);
                                  y = LIST_SEARCH (L, l);
                                  LIST_INSERT_BEFORE (L, x, y);
                                  break;

			case 'd': scanf (" %c", &k);
				  x = LIST_SEARCH (L, k);

				  if (x == NULL)
					  printf ("-1\n");
				  else 
					  LIST_DELETE (L, x);
				  break;

			case 'i': LIST_DELETE_FIRST (L);
				  break;

			case 'l': LIST_DELETE_LAST (L);
				  break;

			case 'p': PRINT_LIST (L);
				  break;

			case 'e': free (L);
				  exit (0);
		}
	}
}
