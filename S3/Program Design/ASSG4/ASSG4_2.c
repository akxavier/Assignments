#include <stdio.h>
#include <limits.h>

struct student {
	int stud_id;
	char stud_name [20];
	int rank;
} S[10000];

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

void Min_Heapify (struct student S[], int i, int heapsize) {
	int l, r, min;
	struct student temp;

	l = Left (i);
	r = Right (i);

	if ( l < heapsize && S[l].rank < S[i].rank )
		min = l;
	else 
		min = i;

	if ( r < heapsize && S[r].rank < S[min].rank )
		min = r;

	if (min != i) {
		temp = S[i];
		S[i] = S[min];
		S[min] = temp;

		Min_Heapify (S, min, heapsize);
	}
}

void Heapsort (struct student S[], int n) {
	struct student temp;
	int heapsize = n;

	for (int i = n - 1; i > 0; i--) {
		temp = S[i];
		S[i] = S[0];
		S[0] = temp;

		heapsize--;

		Min_Heapify (S, 0, heapsize);
	}
}

void Enter (struct student S[], int heapsize) {
	scanf ("%d %s %d", &S[heapsize - 1].stud_id, &S[heapsize - 1].stud_name, &S[heapsize - 1].rank);
	
	struct student temp;

	int i = heapsize - 1;

	while ( i > 0 && S[Parent(i)].rank > S[i].rank ) {
		temp = S[Parent(i)];
		S[Parent(i)] = S[i];
		S[i] = temp;

		i = Parent(i);
	}
}

void Interview (struct student S[], int heapsize) {
	struct student min;

	min = S[0];
	S[0] = S[heapsize - 1];
	heapsize--;

	Min_Heapify (S, 0, heapsize);

	printf ("%d %s\n", min.stud_id, min.stud_name);
}

void List (struct student S[], int heapsize) {
	struct student temp[10000];
	
	for (int i = 0; i < heapsize; i++) 
		temp[i] = S[i];

	Heapsort (temp, heapsize);

	for (int i = heapsize - 1; i >= 0; i--) 
		printf ("%d ", temp[i].stud_id);
	printf ("\n");
}


void main () { 
	char ch, n = 0;

	while (1) {
		scanf ("%c", &ch);

		switch (ch) {
			case 'e': n++;
				  Enter (S, n);
				  break;

			case 'i': if (n == 0)
					  printf ("-1\n");
				  else {
					  Interview (S, n);
					  n--;
				  }
				  break;

			case 'l': if (n == 0)
					  printf ("-1\n");
				  else 
					  List (S, n);
				  break;

			case 't': return;
		}
	}
}
