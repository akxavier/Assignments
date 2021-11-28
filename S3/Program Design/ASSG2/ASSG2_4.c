#include <stdio.h>
#include <string.h>

void InsertionSortAs (int A[], int n) {
	int key, i, j;
	for (i = 1; i < n; i++) {
		key = A[i];

		for (j = i -1; j >= 0; j--) 
			if ( A[j] > key )
				A [j + 1] = A[j];
			else 
				break;	

		A[j + 1] = key;
	}
}

void InsertionSortDs (int A[], int n) {
	int key, i, j;
	for (i = 1; i < n; i++) {
		key = A[i];

		for (j = i - 1; j >= 0; j--) 
			if ( A[j] < key )
				A[j + 1] = A[j];
			else 
				break;
			
		A[j + 1] = key;
	}
}

void Print ( int A[], int n ) {
	for (int i = 0; i < n; i++) 
	       printf ("%d ", A[i]);
	printf ("\n");
}	

void main () {
	int A[20], B[10], C[10], n, evenc = 0, oddc = 0;
	
	void Print ( int[], int );

	scanf ("%d", &n);

	for (int i = 0; i < n; i++) 
		scanf ("%d", A + i);

	for (int i = 0; i < n; i += 2)
		B[evenc++] = A[i];

	for (int i = 1; i < n; i += 2)
		C[oddc++] = A[i];

	InsertionSortAs (B, evenc);
	InsertionSortDs (C, oddc);

	Print (B, evenc);
	Print (C, oddc);

}
