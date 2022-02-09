#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

struct node {
	char name[30];
	struct node *next;
	struct node *prev;
};

typedef struct node *node;

node Create_Node () {
	node x = (node) malloc (sizeof (struct node));
	x -> next = NULL;
	x -> prev = NULL;

	return x;
}

int Pos (char ch) {
	int pos;

	if ( isupper(ch) )
		pos = ( (int) ch ) - 64;
	else
		pos = ( (int) ch ) - 96;

	return pos;
}

int Hash (char *str, int n) {
	int len = strlen (str);
	int sum = 0;

	for (int i = 0; i < len; i++) {
		sum += ( Pos( str[i] ) * pow(3, i) );
	}

	return ( sum % n );
}

void Insert (struct node **T, node x, int n) {
	int index = Hash (x -> name, n);

	if ( T[index] == NULL )
		T[index] = x;

	else {
		node current = T[index];

		current -> prev = x;
		x -> next = current;
		T[index] = x;
	}
}

void Delete (struct node **T, char *str, int n) {
	int index = Hash (str, n);

	node current = T[index];

	if (current -> name == str) {
		T[index] = NULL;
		free (current);
		return;
	}

	while ( (current -> name != str) && (current != NULL) )
		current = current -> next;

	if (current == NULL)
		return;

	if (current -> next == NULL) {
		current -> prev -> next = NULL;
		free(current);
	}

	else {
		current -> prev -> next = current -> next;
		current -> next -> prev = current -> prev;
		free (current);
	}
}

int Check_OnetoOne (struct node **T, int n) {
	for (int i = 0; i < n; i++) {
		if (T[i] != NULL) {
			if (T[i] -> next != NULL)
				return 0;
		}
	}

	return 1;
}

void main () {
	char ch, str[30];
	node x;
	int n;

	scanf ("%d", &n);

	node T[n];
	
	for (int i = 0; i < n; i++) {
		T[i] = NULL;
	}

	while (1) {
		scanf ("%c", &ch);

		switch (ch) {
			case 'i': x = Create_Node();
				  scanf (" %s", x -> name);
				  Insert (T, x, n);
				  break;

			case 'd': scanf (" %s", str);
				  Delete (T, str, n);
				  break;

			case 'p': if ( Check_OnetoOne(T, n) )
					  printf ("1\n");
				  else 
					  printf ("-1\n");
				  break;

			case 't': exit(0);
		}
	}
}
