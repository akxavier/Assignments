#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<limits.h>

typedef struct node *node;
typedef struct edge *edge;

struct node {
	int no;
	int dist;
	struct node *prev;
};

struct edge {
	int w;
	node u;
	node v;
};

void Init_Source(node nodeList, int n, int s) {
	for(int i = 0; i < n; i++) {
		nodeList[i].dist = INT_MAX;
		nodeList[i].prev = NULL;
	}
	nodeList[s].dist = 0;
	nodeList[s].prev = &nodeList[s];
}

void RELAX(node u, node v, int w) {
	if( u->dist != INT_MAX ) {
		if( (u->dist + w) < v->dist ) {
			v->dist = u->dist + w;
			v->prev = u;
		}
	}
}

bool BELLMAN_FORD(node nodeList, int n, edge edgeList, int m, int s) {
	Init_Source(nodeList, n, s);

	for(int i = 0; i < n - 1; i++) {
		for(int j = 0; j < m; j++) {
			RELAX(edgeList[j].u, edgeList[j].v, edgeList[j].w);
			RELAX(edgeList[j].v, edgeList[j].u, edgeList[j].w);
		}
	}

	for(int i = 0; i < m; i++) {
		if(edgeList[i].v->dist > edgeList[i].u->dist + edgeList[i].w)
			return false;
		if(edgeList[i].u->dist > edgeList[i].v->dist + edgeList[i].w)
			return false;
	}

	return true;
}

void printNext(node src, node dst) {
	if(dst->prev == NULL) {
		printf("Destination Unreachable\n");
	} else {
		while(dst->prev != src)
			dst = dst->prev;
		printf("%d", dst->no);
	}
}

void traceRoute(node dst) {
	if(dst-> prev == NULL)
		printf("Destination Unreachable\n");
	else if(dst->prev == dst) {
		printf("%d ", dst->no);
	} else {
		traceRoute(dst->prev);
		printf("%d ", dst->no);
	}
}

int main() {
	int n, m;
	// n - no of nodes, m - no of edges
	
	scanf("%d %d", &n, &m);
	node nodeList = (node) malloc (n * sizeof(struct node));
	edge edgeList = (edge) malloc (m * sizeof(struct edge));

	for(int i = 0; i < n; i++) {
		nodeList[i].no = i;
	}

	for(int i = 0; i < m; i++) {
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		edgeList[i].w = w;
		edgeList[i].u = &(nodeList[u]);
		edgeList[i].v = &(nodeList[v]);
	}

	for(int i = 0; i < n; i++) {

		if(!BELLMAN_FORD(nodeList, n, edgeList, m, i)) {
			printf("ERROR: Graph contains negative cycles.\n");
			return 1;
		}

		printf("\nRouting Table for Node %d:\n", i);

		printf(" Dst \tNext \tCost \tPath");
		for(int j = 0; j < n; j++) {
			printf("\n %d \t", j);
			printNext(nodeList+i, nodeList+j);
			printf("\t%d \t", nodeList[j].dist);
			traceRoute(nodeList+j);
		}
		printf("\n");
	}

	return 0;
}
