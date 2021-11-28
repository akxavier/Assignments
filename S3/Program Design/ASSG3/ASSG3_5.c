#include <stdio.h>
#include <limits.h>

int count = 0, inv_c = 0;

void Merge (int A[], int p, int q, int r) {
	int L[50000], R[50000];

	int m = q - p + 1;
	int n = r - q;

	for (int i = 0; i < m; i++) 
		L[i] = A[p + i];

	for (int i = 0; i < n; i++)
		R[i] = A[q + 1 + i];

	L[m] = R[n] = INT_MAX;

	for (int k = p, i = 0, j = 0; k <=r; k++) {
		if (L[i] <= R[j])
			A[k] = L[i++];
		else {
			inv_c += (m - i);
			A[k] = R[j++];
		}
		count++;
	}
}

void Merge_sort (int A[], int p, int r) {
	if (p < r) {
		int q = (p + r) / 2;
		Merge_sort (A, p, q);
		Merge_sort (A, q + 1, r);
		Merge (A, p, q, r);
	}
}

void main () {
	int A[100000], n;
	scanf ("%d", &n);

	for (int i = 0; i < n; i++)
		scanf ("%d", A + i);

	Merge_sort(A, 0, n - 1);

	printf ("%d\n%d", inv_c, count);
}
