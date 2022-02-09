#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
	char *word;
	struct node *next;
};

typedef struct node *node;

void main () {
	node table[400], x, current;
	char str[500];
	int len, hash_val;

	int k;
	scanf ("%d\n", &k);

	for (int i = 0; i < k; i++) {
		table[i] = NULL;
	}

	scanf ("%[^\n]", str);

	char *token = strtok(str, " ");

	while (token != NULL) {
		x = (node) malloc (sizeof (struct node));
		x -> word = token;
		x -> next = NULL;

		len = strlen(token);
		hash_val = (len * len) % k;

		if (table[hash_val] == NULL) {
			table[hash_val] = x;
		}

		else {
			current = table[hash_val];

			while (current != NULL) {
				if ( strcmp(current -> word, x -> word) == 0) {
					break;
				}

				if (current -> next == NULL) {
				       current -> next = x;
				       break;
				}

				current = current -> next;
			}
		}

		//printf ("%s\n", token);

		token = strtok(NULL, " ");
	}

	for (int i = 0; i < k; i++) {
		printf ("%d:", i);

		current = table[i];

		if (current == NULL) {
			printf ("null\n");
			continue;
		}

		while (current -> next != NULL) {
			printf ("%s-", current -> word);
			current = current -> next;
		}

		printf ("%s\n", current -> word);
	}
}

