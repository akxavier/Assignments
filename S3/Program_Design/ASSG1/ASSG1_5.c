#include <stdio.h>
 
void main () {
	int A[100], B[100], temp[20], m, n, i, j, x = 0, flag, element;

	scanf ("%d %d", &m, &n);
	
	for (i = 0; i < m; i++)
		scanf ("%d", A + i);
	for (i = 0; i < n; i++)
		scanf ("%d", B + i);

	for (i = 0; i < m; i++) {
		element = A[i];
		flag = 0;

		for (j = 0; j < x; j++) 
			if (temp[j] == element) {
				flag = 1;
				break;
			}

		if (flag == 1)
			continue;

		for (j = i + 1; j < m; j++) 
			if (A[j] == element) {
				temp[x++] = element;
				flag = 1;
				break;
			}

		if (flag == 0) 
			for (j = 0; j < n; j++) 
				if (B[j] == element) {
					temp[x++] = element;
					break;
				}
	}

	for (i = 0; i < n; i++) {
		element = B[i];
		flag = 0;

		for (j = 0; j < x; j++) 
			if (temp[j] == element) {
				flag = 1;
				break;
			}

		if (flag == 1)
			continue;

		for (j = i + 1; j < n; j++) 
			if (B[j] == element) {
				temp[x++] = element;
				break;
			}
	}

	for (i = 0; i < x; i++) {
		for (j = 0; j < m; j++)
			if (temp[i] == A[j])
				printf ("%d ", A[j]);
		for (j = 0; j < n; j++)
			if (temp[i] == B[j])
				printf ("%d ", B[j]);
	}

	for (i = 0; i < m; i++) {
		flag = 0;
		for (j = 0; j < x; j++)
			if (temp[j] == A[i])
				flag = 1;
		if (flag == 0)
			printf ("%d ", A[i]);
	}

	for (i = 0; i < n; i++) {
		flag = 0;
		for (j = 0; j < x; j++)
			if (temp[j] == B[i])
				flag = 1;
		if (flag == 0)
			printf ("%d ", B[i]);
	}
}	
