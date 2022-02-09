#include <stdio.h>
#include <stdlib.h>

struct table {
	int m;
	int arr[100];
	int c1;
	int c2;
	char probe;
};

typedef struct table* table;

int Is_Prime (int n) {
	if (n < 1)
		return 0;

	for (int i = 2; i <= n / 2; i++) {
		if (n % i == 0) {
			return 0;
		}
	}

	return 1;
}

void Hash_Insert(table T, int k) {

	// Quadratic Probing
	// h(k,i) = (h1(k) + C1*i + C2*i*i) mod m
	// h1(k) = k mod m
	if (T -> probe == 'a') {
		int hash_val;
		hash_val = k % T -> m;

		if (T -> arr[hash_val] == -1) {
			T -> arr[hash_val] = k;
		}

		else {
			for (int i = 1; i < T -> m; i++) {
				hash_val = ( (k % T -> m) + (T -> c1 * i) + (T -> c2 * i * i) ) % T -> m;

				if (T -> arr[hash_val] == -1) {
					T -> arr[hash_val] = k;
					break;
				}
			}
		}
	}

	// Double Hashing
	// h(k, i) = (h1(k) + i*h2(k)) mod m
	// h1(k) = k mod m
	// h2(k) = R - (k mod R); where R = largest prime less than m
	else if (T -> probe == 'b') {
		int primes[28];
		int n = 0;
		for (int i = 1; i <= 100; i++) {
			if ( Is_Prime(i) ) {
				primes[n++] = i;
			}
		}

		n = 0;

		while (primes[n] < T -> m) {
			n++;
		}

		int R = primes[n - 1];

		int hash_val;

		for (int i = 0; i < T -> m; i++) {
			hash_val = ( (k % T -> m) + i * (R - (k % R)) ) % T -> m;

			if (T -> arr[hash_val] == -1) {
				T -> arr[hash_val] = k;
				break;
			}
		}
	}
}

int Hash_Search (table T, int k) {
	int pos = -1;

	if (T -> probe == 'a') {
                int hash_val;
                hash_val = k % T -> m;

                if (T -> arr[hash_val] == k) {
                        pos = hash_val;
                }

                else {
                        for (int i = 1; i < T -> m; i++) {
                                hash_val = ( (k % T -> m) + (T -> c1 * i) + (T -> c2 * i * i) ) % T -> m;

                                if (T -> arr[hash_val] == k) {
                                        pos = hash_val;
                                        break;
                                }
                        }
                }
        }

	else if (T -> probe == 'b') {
                int primes[28];
                int n = 0;
                for (int i = 1; i <= 100; i++) {
                        if ( Is_Prime(i) ) {
                                primes[n++] = i;
                        }
                }

                n = 0;

                while (primes[n] < T -> m) {
                        n++;
                }

                int R = primes[n - 1];

                int hash_val;

                for (int i = 0; i < T -> m; i++) {
                        hash_val = ( (k % T -> m) + i * (R - (k % R)) ) % T -> m;

                        if (T -> arr[hash_val] == k) {
                                pos = hash_val;
                                break;
                        }
                }
        }

	return pos;
}

void Hash_Delete (table T, int k) {
	int pos = Hash_Search (T, k);

	T -> arr[pos] = -1;
}

void Print_Table (table T) {
	for (int i = 0; i < T -> m; i++) {
		if (T -> arr[i] == -1) {
			printf ("%d ()\n", i);
		}

		else {
			printf ("%d (%d)\n", i, T -> arr[i]);
		}
	}
}

void main () {
	table T;
	T = (table) malloc (sizeof (struct table));

	char ch;
	int k;

	scanf ("%c", &T -> probe);
	scanf ("%d", &T -> m);
	
	for (int i = 0; i < T -> m; i++)
		T -> arr[i] = -1;

	if (T -> probe == 'a') {
		scanf ("%d %d", &T -> c1, &T -> c2);
	}

	while (1) {
		scanf ("%c", &ch);

		switch (ch) {
			case 'i': scanf (" %d", &k);
				  Hash_Insert(T, k);
				  break;

			case 's': scanf (" %d", &k);
				  if ( Hash_Search(T, k) == -1)
					  printf ("-1\n");
				  else
					  printf ("1\n");

				  break;

			case 'd': scanf (" %d", &k);
				  Hash_Delete(T, k);
				  break;

			case 'p': Print_Table(T);
				  break;

			case 't': free(T);
				  exit (0);
		}
	}
}
