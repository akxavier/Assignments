#include <stdio.h>

int Bin_search (int A[], int m, int n, int k) {
	int mid;

	if (m > n)
		return -1;

	mid = (m + n)/2;

	if (A[mid] == k)
		return mid;
	else if (k > A[mid])
		return Bin_search (A, m, mid - 1, k);
	else if (k <  A[mid])
		return Bin_search (A, mid + 1, n, k);
}

void main () {
	int A[1000000], B[1000000], m, n, pos;

	scanf ("%d %d", &m, &n);

	for (int i = 0; i < m; i++) 
		scanf ("%d", A + i);
	for (int i = 0; i < n; i++)
		scanf ("%d", B + i);

	for (int i = 0; i < m; i++) {
		pos = Bin_search (B, 0, n - 1, A[i]);
		if (pos == -1)
			continue;
		else 
			printf ("%d ", A[i]);
	}
}
