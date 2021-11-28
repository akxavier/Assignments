#include <stdio.h>
#include <stdlib.h>

struct stack {
	int top;
	char A [500];
};

void Push (struct stack *S, char ch) {
	S -> top = S -> top + 1;
	S -> A [S -> top] = ch;
}

void Pop (struct stack *S) {
	if (S -> A [S -> top] != '(')
		printf ("%c", S -> A [S -> top]);
	
	S -> top = S -> top - 1;
}

int Priority (char ch) {
	switch (ch) {
		case '*': return 4;
			  break;

		case '/': return 3;
			  break;

		case '+': return 2;
			  break;

		case '-': return 1;
			  break;

		case '(': return 0;
			  break;
	}
}

void Infix_to_Postfix () {
	struct stack *S;
	S = (struct stack *) malloc (sizeof (struct stack));
	S -> top = -1;

	char ch;

	while (1) {
		scanf ("%c", &ch);

		switch (ch) {
			case '*':
			case '/':
			case '+':
			case '-': if (S -> top == -1)
					  Push (S, ch);
				  
				  else {
					  while ( Priority(ch) < Priority(S -> A [S -> top]) ) 
						  Pop (S);

					  Push (S, ch);
				  }
				  break;

			case '(': Push (S, ch);
				  break;

			case ')': while (S -> A [S -> top] != '(')
					  Pop (S);
				  Pop (S);
				  break;

			case '\n': while (S -> top != -1)
					   Pop (S);
				   free (S);
				   exit (0);
				   break;

			default: printf ("%c", ch);
		}
	}
}

void main () {
	Infix_to_Postfix();
}
