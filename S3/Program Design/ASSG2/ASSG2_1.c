#include <stdio.h>

void main () {
	int A[100], n, sum = 0, count = 0;

	scanf ("%d", &n);

	for (int i = 0; i < n; i++) {
		scanf ("%d", A + i);
		if (A[i] >= 0) {
			sum += A[i];
			count++;
		}
	}

	printf ("%d %d", sum, count);
}
