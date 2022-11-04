#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_ELEMENT 100
#define SIZE 10

typedef struct{
    int key;
}element;

typedef struct {
    element heap[MAX_ELEMENT];
    int heap_size;
}HeapType;
HeapType * create() {
    HeapType *tmp = (HeapType*)malloc(sizeof(HeapType));
    return tmp;
}
void init(HeapType *h) {
    h->heap_size = 0;
}

void insert_max_heap(HeapType *h, element item){
    int i = ++(h->heap_size); // 힙의 크기를 1 증가
    while((i!=1) && item.key > h->heap[i/2].key){  // root가 아니고 부모 노드보다 크다면 반복
        h->heap[i] = h->heap[i/2];    // 자식노드에 부모노드 넣기
        i = i/2;                    // i를 부모노드로 바꾸기
    }
    h->heap[i].key = item.key;     // 부모노드에 값 넣기
}

element delete_max_heap(HeapType* h) {
    int parent, child;
    element item, temp;  // root값과 삽입노드 값을 저장
    item = h->heap[1];   // item에 root 가장 큰 값 저장
    temp = h->heap[(h->heap_size)--];   // 힙사이즈 1 줄이고 temp에 저장
    parent = 1;    //
    child = 2;
    while (child <= h->heap_size) {   // 힙사이즈보다 노드번호가 작다면 반복
        if ((child < h->heap_size) && (h->heap[child].key) < h->heap[child + 1].key)  //오른쪽 노드보다 왼쪽노드가 작다면
            child++;                                                           //오른쪽 노드를 선택
        if (temp.key >= h->heap[child].key)   // 삽입 노드가 더크다면 멈춤
            break;
        h->heap[parent] = h->heap[child];  // 아니라면 부모노드에 더 컸던 노드 삽입
        parent = child;   //
        child *= 2;
    }
    h->heap[parent] = temp;
    return item;
}
void print_heap(HeapType *h){
    for(int i = 1; i <= h->heap_size; i++) {
        printf("%3d", h->heap[i].key);
    }
    printf("\n");
}

int menu_display(){
    int menu;
    printf("**이진 트리 구현**\n");
    printf("1. 1~100 사이의 난수 10개 생성\n");
    printf("2. 난수 입력하고 배열 출력\n");
    printf("3. 힙 정렬 수행\n");
    printf("4. 프로그램 종료\n");
    scanf("%d",&menu);
    return menu;
}

void heap_sort(element a[],int n){
    HeapType *h;
    h = create();
    init(h);
    printf("\t--힙트리 생성--\n");
    for(int i = 0; i < SIZE ; i++) {
        insert_max_heap(h,a[i]);
        print_heap(h);
    }
    printf("\t--힙정렬 수행--\n");
    for(int i = (n-1); i>= 0 ; i--) {
        a[i] = delete_max_heap(h);
        print_heap(h);
    }
    free(h);
}

int main(){
    srand(time(NULL));
    HeapType* heap;
    element e[MAX_ELEMENT];
    while (1) {
        switch (menu_display()) {
            case 1:
                for (int i = 0; i < 10; i++) {
                    e[i].key = rand() % 100 + 1;
                }
                break;
            case 2:

                heap = create();
                init(heap);
                for (int i = 0; i < 10; i++) {
                    insert_max_heap(heap, e[i]);
                    print_heap(heap);
                }
                break;
            case 3:
                heap_sort(e,SIZE);
                printf("\t--힙정렬 완료(오름차순 정렬)--\n");
                for(int i = 0; i < SIZE; i++) {
                    printf("%3d ", e[i].key);
                }
                printf("\n");
                break;

            case 4:
                exit(0);
    }
    }
    free(heap);
}