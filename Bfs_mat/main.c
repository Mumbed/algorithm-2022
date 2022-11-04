#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 10
typedef int element;
typedef struct { // 큐 타입
    element  queue[MAX_QUEUE_SIZE];
    int  front, rear;
} QueueType;
// 오류 함수
void error(const char* message){
    fprintf(stderr, "%s\n", message);
    exit(1);
}
// 공백 상태 검출 함수
void queue_init(QueueType* q){
    q->front = q->rear = 0;
}
// 공백 상태 검출 함수
int is_empty(QueueType* q){
    return (q->front == q->rear);
}
// 포화 상태 검출 함수
int is_full(QueueType* q){
    return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}
// 삽입 함수
void enqueue(QueueType* q, element item){
    if (is_full(q))
        error("큐가 포화상태입니다");
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->queue[q->rear] = item;
}
// 삭제 함수
element dequeue(QueueType* q){
    if (is_empty(q))
        error("큐가 공백상태입니다");
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->queue[q->front];
}
#define MAX_VERTICES 5
#define TRUE 1
#define FALSE 0

//인접 행렬로 그래프 표현
typedef struct GraphType {
    int n; // 정점의 수
    int adj_mat[MAX_VERTICES][MAX_VERTICES]; // 인접 행렬 - 행과 열
}GraphType;

int visited[MAX_VERTICES];   //방문했는지에 대한 배열 0 과 1로 구별
//초기화
void init(GraphType *g){
    g->n = 0;
    for(int r=0; r<MAX_VERTICES; r++){
        for(int c=0; c<MAX_VERTICES; c++){
            g->adj_mat[r][c] = 0;
        }
    }
}
void insert_vertex(GraphType *g, int v){
    if((g->n)+1>MAX_VERTICES) {
        printf("정점 개수 초과\n");
        return;
    }
    g->n++;
}
void insert_edge(GraphType *g, int start, int end){
    if(start>=g->n || end >= g->n) {
        return;
    }
    //무방향 그래프일 때
    g->adj_mat[start][end] = 1;
    g->adj_mat[end][start] = 1;
}
void print_adj_mat(GraphType* g) {
    for (int i = 0; i < g->n; i++) {
        for (int j = 0; j < g->n; j++) {
            printf("%2d ", g->adj_mat[i][j]);
        }
        printf("\n");
    }
}
//너비 우선 탐색 (무방향 그래프): 큐를 사용함
void bfs_mat(GraphType *g, int v){
    QueueType q;
    queue_init(&q);
    visited[v] = TRUE;
    printf("정점 %d -> ",v);
    enqueue(&q,v);    // v를 방문했다고 찍고 큐에 담음
    while(!is_empty(&q)) {    // 큐가 빌 때가지
        v = dequeue(&q);    // 처음에 v 가 빠짐
        for(int w= 0; w < g->n; w++){
            if(g->adj_mat[v][w] && !visited[w]){
                visited[w] = TRUE;
                printf("정점 %d -> ",w);
                enqueue(&q,w);  // [v][~] 1의 거리의 방문 가능한 정점을 큐에 모두 담음
            }
        }
    }
}

int main() {
    GraphType *g;
    g = (GraphType *) malloc(sizeof(GraphType));
    init(g);
    for (int i = 0; i < MAX_VERTICES; i++) {
        insert_vertex(g, i);
    }
    //간선의 표현
    insert_edge(g, 0, 1);
    insert_edge(g, 0, 2);
    insert_edge(g, 0, 4);
    insert_edge(g, 1, 2);
    insert_edge(g, 2, 3);
    insert_edge(g, 3, 4);
    print_adj_mat(g);                 //스택에서 하나씩 빼면서 방문할 점점이 있는지 확인
    printf("너비 우선 탐색 결과\n");
    bfs_mat(g,0);
}