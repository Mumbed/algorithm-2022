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
#define MAX_VERTICES 10
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
//실행 될 때마다 정점의 수 ++
void insert_vertex(GraphType *g, int v){
    if((g->n)+1>MAX_VERTICES) {
        printf("정점 개수 초과\n");
        return;
    }
    g->n++;
}
// start end에 따라 방문함을 알림
void insert_edge(GraphType *g, int start, int end){
    if(start>=g->n || end >= g->n) {  //정점 간선
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
//재귀함수(스택)을 사용한 깊이 우선 탐색 (무방향 그래프)알고리즘
void dfs_mat(GraphType* g, int v) { // 0
    visited[v] = TRUE;
    printf("정점 %d -> ",v);
    for(int w = 0; w < g->n; w++) {
        if (g->adj_mat[v][w] && !visited[w] ) {  //깊이 우선이기 때문에 재귀함수를 통해 점점 안으로 들어감
            dfs_mat(g, w); // recursive
        }
    }
}
//너비 우선 탐색 (무방향 그래프): 큐를 사용함
void bfs_mat(GraphType *g, int v){
    QueueType q;
    queue_init(&q);
    visited[v] = TRUE;
    printf("정점 %d -> ",v);
    enqueue(&q,v);
    while(!is_empty(&q)) {
        v = dequeue(&q);
        for(int w= 0; w < g->n; w++){
            if(g->adj_mat[v][w] && !visited[w]){
                visited[w] = TRUE;
                printf("정점 %d -> ",w);
                enqueue(&q,w);
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
    insert_edge(g, 0, 1);    //0은 방문으로 처리 스택에 0 저장 첫번째 1을 만났기에 스택에 1을 넣어야함 0 1 1 0 1
    insert_edge(g, 1, 2);    // 배열을 하나 만들어서 방문했는지 표시 ex T T F F F 0 과 일은 방문한적 있음 2번으로 가야함
    insert_edge(g, 1, 3);
    insert_edge(g, 2, 4);    //1번으로 와서 (1-0은 방문한것으로 처리)   T T F F F 였기에 2번 방문하면서 T T T F F  스택에 2 저장
    insert_edge(g, 3, 4);    // 1 1 0 1 1 3번 연결이네?  T T T T F 스택에 3 저장
    insert_edge(g, 3, 5);
    insert_edge(g, 5, 6);
    insert_edge(g, 5, 7);
    insert_edge(g, 7, 8);
    insert_edge(g, 7, 9);
    //insert_edge(g, 3, 4);    // 3에서 갈 수 있는 곳 3 - 4 T T T T T 스택에 4 저장
    print_adj_mat(g);                 //스택에서 하나씩 빼면서 방문할 점점이 있는지 확인
    //DFS 깊이 우선 탐색
    printf("깊이 우선 탐색 결과\n");   // 3 1 0 2 4 5 6
    dfs_mat(g,3);
    printf("\n");

}