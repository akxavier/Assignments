#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

struct node {
	char word [100];
	struct node *next;
};

typedef struct node *node;

node Create_Node (char *str) {
	node x = (node) malloc (sizeof (struct node));
	x -> next = NULL;
	strcpy (x -> word, str);

	return x;
}

int Find_Hash1 (char *word, int n) {
	int len = strlen (word);

	if (len == 1) {
		return ( (2 * (int) word[0]) % n );
		printf ("Hello\n");
	}

	else {
		double sum = (int)word[0] + (int)word[1] + (int)word[len-2] + (int)word[len-1];

		int avg = ceil (sum / len);
		
		return ( avg % n );
	}
}

int Find_Hash2 (char *word, int n) {
	int len = strlen(word);

	int sum = 0;
	for (int i = 0; i < len; i++) {
		sum += (int) word[i];
	}

	int avg = sum / len;

	return ( avg % n);
}

void Insert (node *H, node x, int pos) {
	if (H[pos] == NULL) {
		H[pos] = x;
	}

	else {
		node current = H[pos];

		while (current -> next != NULL) {
			current = current -> next;
		}

		current -> next = x;
	}
}

void Store_Word (node *H, int n, char *word) {
	node x = Create_Node (word);

	int h = Find_Hash1 (word, n);
	int g = Find_Hash2 (word, n);

	int cnt_h = 0, cnt_g = 0;

	node current = H[h];

	while (current != NULL) {
		cnt_h++;
		current = current -> next;
	}

	current = H[g];

	while (current != NULL) {
		cnt_g++;
		current = current -> next;
	}

	if (cnt_h <= cnt_g)
		Insert (H, x, h);
	else
		Insert (H, x, g);
}

void Print_Table (node *H, int n) {
	for (int i = 0; i < n; i++) {
		if (H[i] == NULL) {
			printf ("NULL\n");
		}

		else {
			node current = H[i];
			while (current != NULL) {
				printf ("%s ", current -> word);
				current = current -> next;
			}

			printf ("\n");
		}
	}
}

void main () {
	node H[100000], x;
	char str[100000];
	int n;
	char *token;

	scanf ("%d\n", &n);

	for (int i = 0; i < n; i++) {
		H[i] = NULL;
	}

	scanf ("%[^\n]", str);

	token = strtok(str, " ");

	while (token != NULL) {
		Store_Word (H, n, token);
		token = strtok(NULL, " ");
	}

	Print_Table (H, n);
}
