#include <stdio.h>
#include <stdlib.h>

struct stack {
	int top;
	int A [10000];
};

void Push (struct stack *S, int k) {
	S -> top = S -> top + 1;
	S -> A [S -> top] = k;
}

int Pop (struct stack *S) {
	S -> top = S -> top - 1;
	return S -> A [S -> top + 1];
}

int Evaluate_Postfix (struct stack *S, char e[]) {
        int x, y, res;
	char str [4];

        for (int i = 0; e[i] != '\0'; i ++) {

                switch (e[i]) {
                        case '*':
                        case '/':
                        case '+':
                        case '-': y = Pop (S);
				  x = Pop (S);
				  res = (e[i] == '*') ? (x * y) : (e[i] == '/') ? (x / y) : (e[i] == '+') ? (x + y) : (x - y);
				  Push (S, res);
				  break;

			case ' ': break;

			default: y = 0;
				 while (e[i] != ' ') {
					 str [y++] = e[i];
					 i++;
				 }
				 str [y] = '\0';
				 
				 x = atoi (str);
				 Push (S, x);
				 break;
		}
	}

	return S -> A [S -> top];
}

void main () {
	struct stack *S;
	S = (struct stack *) malloc (sizeof (struct stack));
	S -> top = -1;

	char e[100000];

	int i = -1;
	do {
		i++;
		scanf ("%c", &e[i]);
	} while (e[i] != '\n');

	e [i] = e [i + 1] = '\0';

	int x = Evaluate_Postfix (S, e);
	printf ("%d", x);
}
