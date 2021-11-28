#include <stdio.h>

int gcd (int a, int b) {
	int x;
	x = (b == 0) ? a : gcd (b, a%b);
	return x;
}

void main () { 
	int a, b, x;
	scanf ("%d %d", &a, &b);

	x = gcd (a, b);

	printf ("%d", x);
}
