#include <stdio.h>
#include <stdlib.h>
#define INF 1000L
#define MAX_VERTICES 100
#define TRUE 1
#define FALSE 0
int A[MAX_VERTICES][MAX_VERTICES];
typedef struct GraphType4{
    int n;
    int weight[MAX_VERTICES][MAX_VERTICES];
}GraphType4;
void printA(GraphType4 *g4){
    int i, j;
    printf("====================================================\n");
    for(i=0; i < g4->n; i++){
        for(j=0; j < g4->n; j++){
            if(A[i][j] == INF)
                printf(" * ");
            else
                printf("%3d ", A[i][j]);
        }
        printf("\n");
    }
    printf("====================================================\n");
}
void floyd(GraphType4* g4) {
    int i, j, k;
    for (i = 0; i < g4->n; i++)
        for (j = 0; j < g4->n; j++)
            A[i][j] = g4->weight[i][j];
    printA(g4);
    for (k = 0; k < g4->n; k++) {
        for (i = 0; i < g4->n; i++)
            for (j = 0; j < g4->n; j++)
                if (A[i][k] + A[k][j] < A[i][j])
                    A[i][j] = A[i][k] + A[k][j];
        printA(g4);
    }
}

int main(void) {
    GraphType4 g4 = {7,
                     {{ 0, 7, INF, INF, 3, 10, INF },
                     { 7, 0, 4, 10, 2, 6, INF },
                     { INF, 4, 0, 2, INF, INF, INF },
                     { INF, 10, 2, 0, 11, 9, 4 },
                     { 3, 2, INF, 11, 0, INF, 5 },
                     { 10, 6, INF, 9, INF, 0, INF },
                     { INF, INF, INF, 4, 5, INF, 0 } }
    };
    floyd(&g4);
}