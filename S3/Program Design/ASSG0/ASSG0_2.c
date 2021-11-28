#include <stdio.h>

int PALINDROME (int);

void main () {
	int A[10000], n, count = 0;
	scanf ("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf ("%d", A+i);
	}

	for (int i = 0; i < n; i++) {
		if (PALINDROME(A[i]) == 1)
				count++;
	}
	printf ("%d", count);
}

int PALINDROME (int a) {
	int rev = 0, digit, x;
	x = a;

	while (x > 0) {
		digit = x % 10;
		rev = (rev * 10) + digit;
		x /= 10;
	}
	if (rev == a)
		return 1;
	else 
		return 0;
}
