#include <stdio.h>

void sort (int A[], int n) {
	int key, i, j;

	for (i = 1; i < n; i++) {
		key = A[i];

		for (j = i - 1; j >= 0; j--) {
			if (A[j] > key)
				A[j + 1] = A[j];
			else break;
		}

		A[j + 1] = key;
	}
}

void main () {
	int A[1000], n, m, minsum = 0, maxsum = 0;

	scanf ("%d %d", &n, &m);

	for (int i = 0; i < n; i++) 
		scanf ("%d", A + i);

	sort (A, n);

	for (int i = 0; i < n - m; i++) 
		minsum += A[i];

	for (int i = 1; i < n - m + 1; i++)
	       maxsum += A[n - i];

	printf ("%d", maxsum - minsum);
}	
