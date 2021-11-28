#include <stdio.h>

void main () {
	int A[10000], B[10], n, i, j, x = 0, count, element, flag;
	
	scanf ("%d", &n);
	for (i = 0; i < n; i++) 
		scanf ("%d", A + i);
	
	for (i = 0; i < n; i++) {
		element = A[i];
		flag = 0;

		for (j = 0; j < x; j++)  
			if (B[j] == element) 
				flag = 1;

		if (flag == 1)
			continue;

		for (j = i + 1; j < n; j++) 
			if (A[j] == element) {
				B[x] = element;
				x++;
				break;
			}
	}

	for (i = 0; i < x; i++) {
		count = 0;
		printf ("%d ", B[i]);

		for (j = 0; j < n; j++) 
			if (A[j] == B[i]) {
				printf ("%d ", j);
				count++;
			}

		printf ("%d\n", count);
	}
	
	if (x == 0) 
		printf ("-1");
}
