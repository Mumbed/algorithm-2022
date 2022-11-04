#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 10

typedef int element;
typedef struct{
    element queue[MAX_QUEUE_SIZE];
    int front, rear;
}QueueType;
void queue_init(QueueType* q){
    q->front = q->rear = 0;
}
void error(const char *message){
    fprintf(stderr, "%s\n", message);
    exit(1);
}
int is_full(QueueType* q){
    return (q->rear+1) % MAX_QUEUE_SIZE == q->front;
}
void enqueue(QueueType* q, element item){
    if(is_full(q)){
        error("큐가 포화상태임");
    }
    q->rear = q->rear + 1 % MAX_QUEUE_SIZE;
    q->queue[q->rear] = item;
}
int is_empty(QueueType* q){
    return q->rear == q->front;
}
int dequeue(QueueType* q) {
    if (is_empty(q))
        error("큐가 공백상태입니다.");
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->queue[q->front];
}

#define MAX_VERTICES 100
#define TRUE 1
#define FALSE 0
int visited[MAX_VERTICES];
typedef struct GraphNode{
    int vertex;
    struct GraphNode* link;
} GraphNode;
typedef struct GraphType{
    int n;
    GraphNode* adj_list[MAX_VERTICES];
}GraphType;

int visited[MAX_VERTICES];

void init(GraphType *g){
    int v;
    g->n = 0;
    for(v = 0; v < MAX_VERTICES; v++){
        g->adj_list[v] = NULL;
    }
}

void insert_vertex(GraphType *g, int v){
    if(((g->n)+1) > MAX_VERTICES){
        fprintf(stderr,"그래프: 정점의 개수 초과");
        return;
    }
    g->n++;
}
void insert_edge(GraphType *g, int u, int v){
    //노드 삽입
    GraphNode *node;
    if( u>= g->n || v>= g->n ){
        fprintf(stderr,"그래프 : 정점 번호 오류");
        return;
    }
    node = (GraphNode *)malloc(sizeof(GraphNode));
    node->vertex = v;
    node->link = g->adj_list[u];
    g->adj_list[u] = node;
}
void print_adj_list(GraphType *g){
    for (int i = 0; i < g->n; i++){
        GraphNode *p = g->adj_list[i];
        printf("정점 %2d의 인접 리스트", i);
        while(p != NULL){
            printf("-> %2d", p->vertex);
            p = p->link;
        }
        printf("\n");
    }
}
void bfs_list(GraphType *g, int v){
    QueueType q;
    queue_init(&q);
    visited[v] = TRUE;
    printf("정점 %d ->", v);
    enqueue(&q, v);
    while(!is_empty(&q)){
        v = dequeue(&q);
        for(GraphNode *w = g->adj_list[v]; w; w = w->link)
            if(!visited[w->vertex]){
                visited[w->vertex] = TRUE;
                printf("%d ->", w->vertex);
                enqueue(&q, w->vertex);
            }
    }
}
int main() {
    GraphType *g;
    g = (GraphType*)malloc(sizeof(GraphType));
    init(g);
    for(int i = 0;i <= 5; i++) {
        insert_vertex(g, i);
    }
    insert_edge(g, 0, 1);
    insert_edge(g, 1, 0);
    insert_edge(g, 0, 2);
    insert_edge(g, 2, 0);
    insert_edge(g, 0, 3);
    insert_edge(g, 3, 0);
    insert_edge(g, 1, 2);
    insert_edge(g, 2, 1);
    insert_edge(g, 1, 4);
    insert_edge(g, 4, 1);
    insert_edge(g, 4, 3);
    insert_edge(g, 3, 4);
    print_adj_list(g);
    printf("너비 우선 탐색\n");
    bfs_list(g, 0);
}
