#include <stdio.h>
#include <stdlib.h>
#define INF 1000L
#define MAX_VERTICES 100
#define TRUE 1
#define FALSE 0
int parent [MAX_VERTICES];
void set_init(int n){
    for(int i=0; i<n; i++){
        parent[i] = -1;
    }
}

//간선의 정보
struct Edge{
int start,end,weight;
};
//그래프 정보
typedef struct GraphType{
    int n; //간선의 개수
    struct Edge edges[2 * MAX_VERTICES];
}GraphType;
void graph_init(GraphType *g){
    g->n= 0;
    for(int i = 0; i < 2* MAX_VERTICES; i++){
        g->edges[i].start = 0;
        g->edges[i].end = 0;
        g->edges[i].weight = 999;
    }
}
void insert_edge(GraphType *g,int start, int end,int weight){
    g->edges[g->n].start = start;
    g->edges[g->n].end = end;
    g->edges[g->n].weight = weight;
    g->n++;
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
void kruskal(GraphType *g){
    //정렬을 위한 함수 qsort()
    int edge_accepted = 0;
    int uset, vset;
    struct Edge e;
    qsort(g->edges, g->n, sizeof(struct Edge),compare);
    set_init(g->n);
    int i =0;
    while(edge_accepted < g->n -1){
        e = g->edges[i];
        uset = set_find(e.start); //5   //2
        vset = set_find(e.end);   //0   //3
        if(uset != vset){
            printf("간선:(%d,%d):%d 선택\n",e.start,e.end,e.weight);
            edge_accepted++;
            set_union(uset,vset);
        }
        i++;
    }
}

int main() {
    GraphType *g;
    g = (GraphType *) malloc(sizeof(GraphType));
    graph_init(g);
    insert_edge(g,0,1,29);
    insert_edge(g,1,2,16);
    insert_edge(g,2,3,12);
    insert_edge(g,3,4,22);
    insert_edge(g,4,5,27);
    insert_edge(g,5,0,10);
    insert_edge(g,6,1,15);
    insert_edge(g,6,3,18);
    insert_edge(g,6,4,25);
    kruskal(g);


}
