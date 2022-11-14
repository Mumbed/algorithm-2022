#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MAX_VERTICES 10
#define TRUE 1
#define FALSE 0
#define INF 1000000
int parent [MAX_VERTICES];
int selected[MAX_VERTICES];
int distance[MAX_VERTICES];
int distance1[MAX_VERTICES];
int found[MAX_VERTICES];
int A[MAX_VERTICES][MAX_VERTICES];
//최소 신장 트리
void set_init(int n){
    for(int i=0; i<n; i++){
        parent[i] = -1;
    }
}
struct Edge{
    int start,end,weight;
};
//그래프 정보
typedef struct GraphType1{
    int n; //간선의 개수
    struct Edge edges[2 * MAX_VERTICES];
}GraphType1;

typedef struct GraphType2{
    int n;
    int weight[MAX_VERTICES][MAX_VERTICES];
}GraphType2;

typedef struct GraphType3{
    int n;
    int weight[MAX_VERTICES][MAX_VERTICES];
}GraphType3;

int get_min_vertex(int n){
    int v;
    for(int i = 0; i<n; i++){
        if(!selected[i]){
            v = i;
            break;
        }
    }
    for(int i = 0; i<n;i++)
        if(!selected[i] && (distance[i] < distance[v]))
            v = i;
    return v;
}

void prim(GraphType2 *g, int s){
    for(int u = 0; u <g->n; u++)
        distance[u] = INF;
    distance[s] = 0;
    int u;
    for(int i=0;i<g->n; i++){
        u = get_min_vertex(g->n);
        selected[u] = TRUE;
        if(distance[u] == INF) return;
        printf("정점 %d 추가\n",u);

        for(int v = 0; v < g->n; v++)
            if(g->weight[u][v] != INF)
                if(!selected[v] && g->weight[u][v]< distance[v])
                    distance[v] = g->weight[u][v];
    }
    for(int i = 0; i < g->n; i++){
        distance[i] = 0;
        selected[i] = FALSE;
    }
}

void graph_init(GraphType1 *g1){
    g1->n= 0;
    for(int i = 0; i < 2* MAX_VERTICES; i++){
        g1->edges[i].start = 0;
        g1->edges[i].end = 0;
        g1->edges[i].weight = 999;
    }
}

void insert_edge(GraphType1 *g1, int start, int end, int weight){
    g1->edges[g1->n].start = start;
    g1->edges[g1->n].end = end;
    g1->edges[g1->n].weight = weight;
    g1->n++;
}

//싸이클 여부를 판정
int set_find(int curr){
    if(parent[curr] == -1)
        return curr;
    while(parent[curr] != -1){
        curr = parent[curr];
    }
    return curr;
}

void set_union(int a, int b){
    int root1 = set_find(a); //5
    int root2 = set_find(b); //0
    if(root1 != root2){
        parent[root1] = root2;
    }
}

//qsort 함수의 정렬방식을 결정하는 함수 1,0,-1 값 중 하나를 리턴
//return 값이 1이면 오름차순 -1 이면 내림차순    같으면 0 return
int compare(const void* a, const void* b){
    struct Edge* x = (struct Edge*)a;
    struct Edge* y = (struct Edge*)b;
    return (x->weight - y->weight);
}

void kruskal(GraphType1 *g1){
    //정렬을 위한 함수 qsort()
    int edge_accepted = 0;
    int uset, vset;
    struct Edge e;
    qsort(g1->edges, g1->n, sizeof(struct Edge),compare);
    set_init(g1->n);
    int i =0;
    while(edge_accepted < g1->n-1){
        e = g1->edges[i];
        uset = set_find(e.start); //5   //2
        vset = set_find(e.end);   //0   //3
        if(uset != vset){
            printf("간선:(%d,%d):%d 선택\n",e.start,e.end,e.weight);
            edge_accepted++;
            set_union(uset,vset);
        }
        i++;
        if(i >10)
            break;
    }
}
//최단경로
int choose(int distance1[], int n, int found[]){
    int min, minpos;
    min = INT_MAX;
    minpos = -1;
    for(int i=0; i<n; i++){
        if(distance[i] < min && !found[i]){
            min = distance[i];
            minpos = i;
        }
    }
    return minpos;
}
void print_status(GraphType3 *g){
    static int step = 1;
    printf("Step %d", step++);
    printf("\n");
    printf("---distance :   ");
    for(int i = 0; i < g->n; i++){
        if(distance[i] == INF)
            printf(" * ");
        else
            printf("%2d ", distance[i]);
    }
    printf("\n");
    printf("---found    :   ");
    for(int i = 0; i < g->n; i++){
        printf("%2d ", found[i]);
    }
    printf("\n\n");
}
void shortest_path(GraphType3 * g, int start){
    int u;
    for(int i = 0; i <g->n; i++){
        distance[i] = g->weight[start][i];
        found[i] = FALSE;
    }
    found[start] = TRUE;
    distance[start] = 0;
    for(int i = 0; i < g->n; i++){
        print_status(g);
        u = choose(distance,g->n,found);
        found[u]= TRUE;
        //distance 배열의 거리값을 재설정
        for(int w = 0; w < g->n; w++){
            if(!found[w]){
                if(distance[u] + g->weight[u][w] < distance[w])
                    distance[w] = distance[u] + g->weight[u][w];
            }
        }
    }
}
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
int menu_display(){
    int menu;
    printf("1. MST(최소 신장 트리) 보기\n");
    printf("2. Shortest Path(최단 경로 알고리즘) 보기\n");
    printf("3. 프로그램 종료 \n");
    scanf("%d",&menu);
    return menu;
}

int main() {
    int a,b;

    while(1){
        int menunum = menu_display();
        if(menunum == 1){
        printf("1. Kruskal 출력\n");
        printf("2. Prim 출력\n");
        scanf(" %d",&a);
        if(a == 1){
            GraphType1 *g1;
            g1 = (GraphType1 *) malloc(sizeof(GraphType1));
            graph_init(g1);
            insert_edge(g1,0,1,29);
            insert_edge(g1,1,2,16);
            insert_edge(g1,2,3,12);
            insert_edge(g1,3,4,22);
            insert_edge(g1,4,5,27);
            insert_edge(g1,5,0,10);
            insert_edge(g1,6,1,15);
            insert_edge(g1,6,3,18);
            insert_edge(g1,6,4,25);
            kruskal(g1);
            free(g1);

        }
        else if (a == 2) {
            GraphType2 g2 = {7,
                           {
                                   {0,29,INF,INF,INF,10,INF},
                                   {29,0,16,INF,INF,INF,15},
                                   {INF,16,0,12,INF,INF,INF},
                                   {INF,INF,12,0,22,INF,18},
                                   {INF,INF,INF,22,0,27,25},
                                   {10,INF,INF,INF,27,0,INF},
                                   {INF,15,INF,18,25,INF,0}
                           }
            };
            prim(&g2,0);
        }
        }
        else if(menunum ==2){
        printf("1. Dijikstra 출력\n");
        printf("2. Floyd  출력\n");
        scanf("%d",&b);
        if(b == 1){
            GraphType3 g3 = {7,
                           {{0, 7, INF, INF, 3, 10, INF},
                            {7, 0, 4, 10, 2, 6, INF},
                            {INF, 4, 0, 2, INF, INF, INF},
                            {INF, 10, 2, 0, 11, 9, 4},
                            {3, 2, INF, 11, 0, INF, 5},
                            {10, 6, INF, 9, INF, 0, INF},
                            {INF, INF, INF, 4, 5, INF, 0}
                           }
            };
            shortest_path(&g3, 0);
        }
        else if (b ==2){
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

    }
    else {
            break;
        }
    }
}
