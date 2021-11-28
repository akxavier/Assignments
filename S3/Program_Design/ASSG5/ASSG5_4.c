#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct queue {
	int head;
	int tail;
	char A[100000][20];
};

int QueueFull (struct queue *Q, int n) {
	if ( ((Q -> head == 0) && (Q -> tail == n - 1)) || (Q -> head == Q -> tail + 1) )
		return -1;
	else 
		return 1;
}

int QueueEmpty (struct queue *Q) {
	if (Q -> head == Q -> tail)
		return -1;
	else
		return 1;
}

void Enqueue (struct queue *Q, char str[], int n) {
	if (QueueFull (Q, n) == -1)
		printf ("-1\n");
	else {
		strcpy (Q -> A[Q -> tail], str);

		if (Q -> tail == n - 1)
			Q -> tail = 0;
		else 
			Q -> tail = Q -> tail + 1;
	}
}

void Dequeue (struct queue *Q, int n) {
	if (QueueEmpty (Q) == -1)
		printf ("-1\n");
	else {
		printf ("%s\n", Q -> A[Q -> head]);

		if (Q -> head == n - 1)
			Q -> head = 0;
		else 
			Q -> head = Q -> head + 1;
	}
}

void main () {
	struct queue *Q;
	Q = (struct queue *) malloc (sizeof (struct queue));
	Q -> head = Q -> tail = 0;

	char ch, str[20];
	int n;

	scanf ("%d", &n);

	while (1) {
		scanf ("%c", &ch);

		switch (ch) {
			case 'i': scanf (" %s", str);
				  Enqueue (Q, str, n);
				  break;

			case 'd': Dequeue (Q, n);
				  break;

			case 'f': if (QueueFull (Q, n) == -1)
					  printf ("-1\n");
				  else 
					  printf ("1\n");
				  break;

			case 'e': if (QueueEmpty (Q) == -1)
					  printf ("-1\n");
				  else
					  printf ("1\n");
				  break;

			case 't': free (Q);
				  exit(0);
		}
	}
}
