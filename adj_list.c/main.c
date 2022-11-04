// 리스트로 구현한 무방향 그래프.
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 50

typedef struct GraphNode {
    int vertex;
    struct GraphNode *link;
}GraphNode;

typedef struct GraphType{
    int n;
    GraphNode * adj_list[MAX_VERTICES];
}GraphType;

void init(GraphType * g){
    g-> n = 0;
    for( int v = 0; v < MAX_VERTICES; v++ ){
        g-> adj_list[v] = NULL; // g 초기화
    }
}

void insert_vertex(GraphType * g, int v){
    if(((g->n)+1) > MAX_VERTICES){ // 정점의 개수가 최대값인 50을 넘는다면
        fprintf(stderr, "그래프 : 정점의 개수 초과");
        return ;
    }
    g-> n++;
}

void insert_edge(GraphType * g, int u, int v){
    GraphNode * node;
    if(u >= g->n || v >= g->n){
        fprintf(stderr, "그래프: 정점 번호 오류");
        return ;
    }
    node = (GraphNode *)malloc(sizeof(GraphNode)); //메모리 공간 동적 할당
    node -> vertex = v;    // g
    node ->link = g->adj_list[u];
    g->adj_list[u] = node;
}

void print_adj_list(GraphType *g){
    for(int i=0; i< g->n;i++){
        GraphNode *node = g->adj_list[i];
        printf("정점 %2d의 인접 리스트 ", i);;
        while (node != NULL){
            printf("-> %2d ", node->vertex);
            node = node->link;
        }
        printf("\n");
    }
}
int main(){
    GraphType *g;
    g = (GraphType *)malloc(sizeof(GraphType));
    init(g);
    for(int i=0; i<4; i++){
        insert_vertex(g, i);
    }
    insert_edge(g,0,1);
    insert_edge(g,1,0);
    insert_edge(g,0,2);
    insert_edge(g,2,0);
    insert_edge(g,0,3);
    insert_edge(g,3,0);
    insert_edge(g,1,2);
    insert_edge(g,2,1);
    insert_edge(g,2,3);
    insert_edge(g,3,2);
    print_adj_list(g);
    free(g);


}