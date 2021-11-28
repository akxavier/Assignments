#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int color [1000], a, b;

struct queue {
	int head;
	int tail;
	int A[1000];
};

void Enqueue (struct queue *Q, int key) {
	Q -> A [Q -> tail] = key;
	if (Q -> tail == 999)
		Q -> tail = 0;
	else 
		Q -> tail = Q -> tail + 1;
}

int Dequeue (struct queue *Q) {
	if (Q -> head == 999) {
		Q -> head = 0;
		return Q -> A [999];
	}
	else { 
		Q -> head = Q -> head + 1;
		return Q -> A [Q -> head - 1];
	}
}

bool isBipartite (int G[][1000], int n) {
	for (int i = 0; i < n; i++)
		color [i] = -1;

	struct queue *Q;
	Q = (struct queue *) malloc (sizeof (struct queue));
	Q -> head = Q -> tail = 0;

	int ver1 = 0, ver2;

	color [ver1] = 0;

	Enqueue (Q, ver1);

	while (Q -> head != Q -> tail) {
		ver1 = Dequeue (Q);

		for (int ver2 = 0; ver2 < n; ver2++) {
			if ( (G [ver1][ver2] == 1) && (color [ver2] == -1) ) {
				color [ver2] = ( color [ver1] ) ? 0 : 1;
				Enqueue (Q, ver2);
			}

			else if ( (G [ver1][ver2] == 1) && (color [ver2] == color [ver1]) ) {
				a = ver1; b = ver2;
				return false;
			}
		}
	}

	free (Q);
	return true;
}

bool isReachable (struct queue *Q, int G [][1000], int n, int start, int end, int prev) {
	if (start == end) {
		Enqueue (Q, end);
		return true;
	}

	for (int i = 0; i < n; i++) {
		if ( (G [start][i] == 1) && (i != prev) && (isReachable (Q, G, n, i, end, start)) ) {
			Enqueue (Q, start);
			return true;
		}
	}
}

void main () {
	int G [1000][1000];
	int m, n, x, y;

	scanf ("%d %d", &n, &m);

	for (int i = 0; i < n; i++) 
		for (int j = 0; j < n; j++)
			G[i][j] = 0;

	for (int i = 0; i < m; i++) {
		scanf ("%d %d", &x, &y);
		G [x][y] = G [y][x] = 1;
	}

	if ( isBipartite (G, n) ) {
		for (int i = 0; i < n; i++) 
			if (color [i] == 0)
				printf ("%d ", i);

		printf ("\n");
		
		for (int i = 0; i < n; i++)
			if (color [i] == 1)
				printf ("%d ", i);
	}

	else {
		struct queue *Q;
		Q = (struct queue *) malloc (sizeof (struct queue));
		Q -> head = Q -> tail = 0;

		if (isReachable (Q, G, n, a, b, b))
			while (Q -> head != Q -> tail)
				printf ("%d ", Dequeue (Q));

		free (Q);
	}
}
