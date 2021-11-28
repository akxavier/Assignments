#include <stdio.h>

void CONVERT (int n) {
	unsigned i;
	for ( i = 1 << 15; i > 0; i /= 2) {
		if ( n & i )
			printf ("1");
		else 
			printf ("0");
	}
	printf ("\n");
}

void main () { 
	int n, k, left, right;

	scanf ("%d %d", &n, &k);

	CONVERT (n);

	left = ( n << k ) | ( n >> (16 - k) );
	CONVERT (left);

	right = ( n >> k ) | ( n << (16 - k) );
	CONVERT (right);
}
	
