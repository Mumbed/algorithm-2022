#include<stdio.h>
#include<stdlib.h>
#define MAX_VERTICES 100
#define TRUE 1
#define FALSE 0
#define INF 1000L //연

int parent[MAX_VERTICES];
void set_init(int n) {//parent 배열 초기화
    for (int i = 0; i < n; i++)
        parent[i] = -1;
}
// 간선의 정보 구조체
struct Edge {
    int start, end, weight; // 시작도착 정점 가중치

};

//그래프 정보 구조체
typedef struct GraphType {
    int n; //간선의 계수
    struct Edge edges[MAX_VERTICES * 2];
}GraphType;


void Graph_init(GraphType*g) {
    g->n = 0;
    for(int i=0;i< MAX_VERTICES * 2;i++){
        g->edges[i].start = 0;
        g->edges[i].end = 0;
        g->edges[i].weight = INF;// 무한대로초기화
    }
}
void insert_edge(GraphType*g,int start, int end , int weight) {
    g->edges[g->n].start = start;
    g->edges[g->n].end = end;
    g->edges[g->n].weight = weight;
    g->n++;

}

int set_find(int curr) {
    if (parent[curr] == -1)//부모노드가 없으면 반환해라
        return curr;
    while (parent[curr] != -1)curr = parent[curr];
    return curr;
}
int set_union(int a,int b) {//간선이면 찍어주고 집합에 넣어라
    int root1 = set_find(a);//5
    int root2 = set_find(b);//0
    if (root1 != root2)
        parent[root1] = root2;
}
int compare(const void*a,const void*b) {//1은 오름 차순 -1 은 내림차순 0 같음리턴함
    struct Edge* x = (struct Edge*)a;
    struct Edge* y = (struct Edge*)b;
    return (x->weight - y->weight);


}
void kruskal(GraphType*g){
    int edge_accepted = 0;
    int uset, vset;
    struct Edge e;
    //정렬 -qsort () 함수
    qsort(g->edges, g->n, sizeof(struct Edge), compare);
    // 간선의 선택 여부는 사이클 여부 , set_union(), set_find()
    set_init(g->n);
    int i = 0;
    printf("크루스칼 최소신장트리 알고리즘");
    while (edge_accepted<(g->n-1)) {
        e = g->edges[i];
        uset = set_find(e.start);//5,2
        vset = set_find(e.end);//0,3
        if (uset != vset) {
            printf("간선( (%d , %d)  %d ) : \n ", e.start, e.end, e.weight);
            edge_accepted++;
            set_union(uset, vset);
        }
        i++;
    }
}

int main(void) {
    GraphType* g;
    g = (GraphType*)malloc(sizeof(GraphType));
    Graph_init(g);
    insert_edge(g, 0, 1, 29);
    insert_edge(g, 1, 2, 16);
    insert_edge(g, 2, 3, 12);
    insert_edge(g, 3, 4, 22);
    insert_edge(g, 4, 5, 27);
    insert_edge(g, 5, 0, 10);
    insert_edge(g, 6, 1, 15);
    insert_edge(g, 6, 3, 18);
    insert_edge(g, 6, 4, 25);

    kruskal(g);

    free(g);

    return 0;
}