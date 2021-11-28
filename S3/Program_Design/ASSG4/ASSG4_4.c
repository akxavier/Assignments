#include <stdio.h>
#include <limits.h>

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

void Min_Heapify (int A[], int i, int heapsize) {
	int l, r, min, temp;

	l = Left (i);
	r = Right (i);

	if ( A[l] < A[i] )
		min = l;
	else 
		min = i;

	if ( A[r] < A[min] )
		min = r;

	if ( min != i ) {
		temp = A[i];
		A[i] = A[min];
		A[min] = temp;

		Min_Heapify (A, min, heapsize);
	}
}

void Change_Token_Number (int A[], int old, int new, int heapsize) {
	int temp, i;

	for (i = 0; i < heapsize; i++) {
		if (A[i] == old)
			break;
	}

	A[i] = new;

	while ( ( i > 0 ) && ( A[Parent(i)] > A[i] ) ) {
		temp = A[Parent(i)];
		A[Parent(i)] = A[i];
		A[i] = temp;

		i = Parent (i);
	}

void Insert_Patient (int A[], int token, int heapsize) {
	int temp;

	A[heapsize - 1] = token;
	
	i = heapsize - 1;

	while ( ( i > 0 ) && ( A[Parent(i)] > A[i] ) ) {
		temp = A[Parent(i)];
		A[Parent(i)] = A[i];
		A[i] = temp;

		i = Parent (i);
	}
}

int Get_Next_Patient (int A[]) {
	return A[0];
}


