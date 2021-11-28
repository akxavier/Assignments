#include <stdio.h>

void main () {
	int oct, dec, digit, n = 1;
	scanf ("%d", &oct);

	while (oct != 0) {
		digit = oct % 10;
		dec = dec + (digit * n);
		oct /= 10;
		n *= 8;
	}

	printf ("%d", dec);
}
