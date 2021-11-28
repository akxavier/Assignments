#include <stdio.h>

int count = 0;

int Parent (int i) {
	int j = i / 2;
	return j;
}

int Left (int i) {
	return 2 * i;
}

int Right (int i) {
	return 2 * i + 1;
}

void Max_Heapify (int A[], int i, int heapsize) {
	int l, r, max, temp;
	l = Left (i);
	r = Right (i);

	max = i;

	if ( l < heapsize ) {
		count++;
		if ( A[l] > A[i] )
			max = l;
	}

	if ( r < heapsize ) {
		count++;
		if ( A[r] > A[max] )
			max = r;
	}

	if (max != i) {
		temp = A[i];
		A[i] = A[max];
		A[max] = temp;

		Max_Heapify (A, max, heapsize);
	}
}

void Build_Max_Heap (int A[], int n) {
	int heapsize = n;
	for (int i = (n / 2) - 1; i >= 0; i--) 
		Max_Heapify (A, i, heapsize);
}

void Heapsort (int A[], int n) {
	int temp, heapsize = n;

	Build_Max_Heap (A, n);

	count = 0;

	for (int i = n - 1; i > 0; i--) {
		temp = A[i];
		A[i] = A[0];
		A[0] = temp;

		heapsize--;

		Max_Heapify (A, 0, heapsize);
	}
}

void main () {
	int A[100000], n;

	scanf ("%d", &n);

	for (int i = 0; i < n; i++) 
		scanf ("%d", A + i);

	Heapsort (A, n);

	for (int i = 0; i < n; i++) 
		printf ("%d ", A[i]);

	printf ("\n%d", count);
}
