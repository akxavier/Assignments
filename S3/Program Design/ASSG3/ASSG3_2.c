#include <stdio.h>

int count = 0, pos = -1;

void Bin_Search (int A[], int m, int n, int k) {
	int mid;
	count++;

	if (m > n)
		return;

	mid = (m + n) / 2;

	if (A[mid] == k) {
		pos = mid;

		if (A[mid - 1] == A[mid])
			Bin_Search (A, m, mid - 1, k);
	}
	else if (k < A[mid])
		Bin_Search (A, m, mid - 1, k);
	else if (k > A[mid])
		Bin_Search (A, mid + 1, n, k);
}

void main () {
	int A[100000], n, k;

	scanf ("%d", &n);

	for (int i = 0; i < n; i++)
		scanf ("%d", A + i);

	scanf ("%d", &k);

	Bin_Search (A, 0, n - 1, k);

	printf ("%d\n%d", pos, count);
}
