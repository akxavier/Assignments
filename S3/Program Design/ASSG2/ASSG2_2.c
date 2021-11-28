#include <stdio.h>

int check ( int n ) {
	int flag = 1, digit;

	while (n > 0) {
		digit = n % 10;
		n /= 10;
		if ( n % 10 > digit ) {
			flag = 0;
			break;
		}
	}

	return flag;
}


void main () {
	int A[10000], B[20], len = 0, n;

	scanf ("%d", &n);

	for (int i = 0; i < n; i++) {
		scanf ("%d", A + i);

		if ( check( A[i] ) == 1) {
			B[len++] = A[i];
		}
	}

	if (len == 0) 
		printf ("-1");
	else
		for (int i = 0; i < len; i++)
			printf ("%d ", B[i]);
}
