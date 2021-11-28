#include <stdio.h>

int count = 0;

int Bin_Search (int A[], int m, int n, int k) {
	int mid;
	count++;

	if (m > n)
		return -1;

	mid = (m + n) / 2;

	if (A[mid] == k)
		return mid;
	else if (k < A[mid])
		return Bin_Search (A, m, mid - 1, k);
	else if (k > A[mid])
		return Bin_Search (A, mid + 1, n, k);
}

void main () {
	int A[100000], n, k, pos;

	scanf ("%d", &n);

	for (int i = 0; i < n; i++)
		scanf ("%d", A + i);

	scanf ("%d", &k);

	pos = Bin_Search (A, 0, n - 1, k);

	printf ("%d\n%d", pos, count);
}
