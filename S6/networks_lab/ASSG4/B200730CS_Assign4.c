// DVR USING BELLMAN FORD ALGO: 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void addStuff(int V, int E, int Graph[V][V])
{
    int src, dst, weight;
    for (int i = 0; i < V; i++) {
    	for(int j = 0; j < V; j++) {
    		if(i == j)
    			Graph[i][j] = 0;
    		else
    			Graph[i][j] = -1;
    	}
    }
    
    for(int i=0;i<E;i++)
    {
        scanf("%d %d %d",&src, &dst, &weight);
        Graph[src][dst] = weight;
        Graph[dst][src] = weight;
    }
}
void bellmanFord(int V, int E, int Graph[V][V], int final[V][V])
{
    for(int i = 0;i < V ; i++)
    {
        for(int j = 0 ; j < V ; j++)
        {
            final[i][j]=Graph[i][j];
            for(int k = 0; k < V ; k ++ )
            {
                if ( ( ( final[i][j] > Graph[k][j]+Graph[i][k] ) || (final[i][j] == -1) ) && (  Graph[k][j] != -1 && Graph[i][k] != -1 ) )
                {
                        final[i][j] = Graph[k][j]+Graph[i][k] ;
                }
            }
            for(int k = 0; k < V ; k++)
            {
                if( ((final[i][k]!=-1)&&(final[k][j]!=-1)) && (final[i][j]==-1) )
                {
                        final[i][j]=final[i][k]+final[k][j];     
                }        
            }
        }
    }
}
void displayTable(int V, int final[V][V], int Graph[V][V])
{ 
    for(int i = 0; i < V; i++) {
    	for(int j = 0; j < V; j++) {
    		printf("%d ", final[i][j]);
    	}
    	
    	printf("\n");
    }
}
int main()
{
    int E, V;
    scanf("%d %d",&V, &E);
    int Graph[V][V], final[V][V];
    memset(Graph, -1, sizeof(Graph[0][0]) * V * V);
    
    addStuff(V, E, Graph);
    bellmanFord(V, E, Graph, final);
    displayTable(V, final, Graph);
}
