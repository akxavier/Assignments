#include <stdio.h>
#include <string.h>

struct amoeba {
	char name [20];
	int size;
} W [1000];

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

void Min_Heapify (struct amoeba W[], int i, int heapsize) {
	int l, r, min;
	struct amoeba temp;

	l = Left (i);
	r = Right (i);

	min = i;

	if ( l < heapsize ) {
		if ( W[l].size < W[i].size ) 
			min = l;
		else if ( ( W[l].size == W[i].size ) && ( strcmp (W[l].name, W[i].name) < 0 ) )
			min = l;
	}

	if ( r < heapsize ) {
		if ( W[r].size < W[min].size )
			min = r;
		else if ( ( W[r].size == W[min].size ) && ( strcmp (W[r].name, W[min].name) < 0) )
			min = r;
	}

	if (min != i) {
		temp = W[i];
		W[i] = W[min];
		W[min] = temp;

		Min_Heapify (W, min, heapsize);
	}
}

void Build_Min_Heap (struct amoeba A[], int n) {
	int heapsize = n;

	for (int i = (n / 2) - 1; i >= 0; i--)
		Min_Heapify (A, i, heapsize);
}

void Insert (struct amoeba A[], struct amoeba a, int heapsize) {
	struct amoeba temp;
	int i = heapsize - 1;

	A[i] = a;

	while (i > 0) {
		if ( (A[Parent(i)].size > A[i].size) || ( ( A[Parent(i)].size == A[i].size ) && (strcmp (A[Parent(i)].name, A[i].name) > 0) ) ) {
			temp = A[i];
			A[i] = A[Parent(i)];
			A[Parent(i)] = temp;
		}

		i = Parent (i);
	}
}

struct amoeba Extract (struct amoeba A[], int heapsize) {
	struct amoeba min;

	min = A[0];
	A[0] = A[heapsize - 1];

	heapsize--;

	Min_Heapify (A, 0, heapsize);

	return min;
}

void Read (struct amoeba a) {
	scanf ("%s %d", a.name, &a.size);
}

struct amoeba Combine (struct amoeba A[], int heapsize) {
	struct amoeba one, two, new;

	one = Extract (A, heapsize);
	two = Extract (A, heapsize - 1);

	strcpy (new.name, one.name);
	new.size = one.size + two.size;

	printf ("%s %s %d\n", one.name, two.name, new.size);

	return new;
}

void main () {
	int n, heapsize = 0;
	struct amoeba a;

	scanf ("%d", &n);

	for (int i = 0; i < n; i++) {
		//Read (a);
		scanf ("%s %d", a.name, &a.size);
		heapsize++;
		Insert (W, a, heapsize);
	}

	while (heapsize > 1) {
		a = Combine (W, heapsize);
		Insert (W, a, heapsize - 1);
		heapsize--;
	}

	printf ("%s %d", W[0].name, W[0].size);
}
