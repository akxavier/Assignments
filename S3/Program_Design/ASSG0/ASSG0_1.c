#include <stdio.h>

void main () {
	int n, rev = 0, digit;
	scanf ("%d", &n);
	int x = n;

	while (x > 0) {
		digit = x % 10;
		rev = (rev * 10) + digit;
		x /= 10;
	}

	if (rev == n)
		printf ("YES");
	else
		printf ("NO");

}
