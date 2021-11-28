#include <stdio.h>
#include <stdlib.h>

struct stack {
	int top;
	char A[100000];
};

int Stack_Empty (struct stack *S) {
	if (S -> top == -1)
		return -1;
	else 
		return 1;
}

int Stack_Full (struct stack *S, int n) {
	if (S -> top == n - 1)
		return -1;
	else 
		return 1;
}

void Push (struct stack *S, char k, int n) {
	if (Stack_Full (S, n) == -1) {
	       printf ("-1\n");
	       return;
	}

	S -> top = S -> top + 1;
	S -> A[S -> top] = k;
}

void Pop (struct stack *S) {
	if (Stack_Empty (S) == -1) {
		printf ("-1\n");
		return;
	}

	S -> top = S -> top - 1;
	printf ("%c\n", S -> A[S -> top + 1]);
}

char Peek (struct stack *S) {
	if (Stack_Empty (S) == -1) 
		return 'a';

	return S -> A[S -> top];
}

void main () {
	struct stack *S;
	S = (struct stack *) malloc (sizeof (struct stack));
	S -> top = -1;

	char ch, c;
	int n;

	scanf ("%d", &n);

	while (1) {
		scanf ("%c", &ch);

		switch (ch) {
			case 'i': scanf (" %c", &c);
				  Push (S, c, n);
				  break;

			case 'd': Pop (S);
				  break;

			case 'p': if (Peek(S) == 'a') {
					  printf ("-1\n");
					  continue;
				  }
				  printf ("%c\n", Peek (S));
				  break;

			case 't': free (S);
				  exit(0);
		}
	}
}
