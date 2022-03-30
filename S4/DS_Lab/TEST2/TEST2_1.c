#include <stdio.h>

void main() {
	int x[100000], y[100000], sum[100000];
	int m, n;

	scanf("%d %d", &n, &m);

	for (int i = n - 1; i >= 0; i--) 
		scanf("%d", x + i);

	for (int i = m - 1; i >= 0; i--)
		scanf("%d", y + i);

	int max = (m > n) ? m : n;

	int carry = 0;
	int elem;
	
	for (int i = 0; i <= max; i++) {
		if ( (i == max) && (carry != 0) ) {
			printf("%d ", carry);
			break;
		}

		if (i >= n)
			x[i] = 0;
		if (i >= m)
			y[i] = 0;

		int ind_sum= x[i] + y[i] + carry;

		carry = ind_sum / 9;
		elem = ind_sum % 9;
		
		sum[i] = elem;
	}

	for (int i = max -1; i >= 0; i--)
		printf("%d ", sum[i]);
}
