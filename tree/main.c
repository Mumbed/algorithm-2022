#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_ELEMENT 100

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
void print_heap(HeapType *h){
    for(int i=1; i<= h->heap_size; i++){
        printf("%d ",h->heap[i].key);
    }
}
void insert_max_heap(HeapType *h, element item){
    int i = ++(h->heap_size);
    //조건 부여
    while((i != 1) && item.key > h->heap[i/2].key) {    // 위로 이동하는 반복문
        h->heap[i] = h->heap[i/2];
        i = i/2;
    }
    h->heap[i].key = item.key;
}

int menu_display(){
    int menu;
    printf("**이진 트리 구현**\n");
    printf("1. 1~100 사이의 난수 10개 생성\n");
    printf("2. 난수 입력하고 배열 출력\n");
    printf("3. 프로그램 종료\n");
    scanf("%d",&menu);
    return menu;
}
//ㅅㅏㄱ제함수
element delete_max_heap(HeapType * h){
    int parent,child;
    element item, temp;

    item = h-> heap[1];
    temp = h-> heap[(h-> heap_size)--];
    parent =1 ;child = 2;
    while(child <= h->heap_size) {
        //왼쪽 자식 오른쪽 자식의 비교
        if( (child < h->heap_size) && (h->heap[child].key ) < (h->heap[child+1].key) ) {
            child++; // 더 큰 키값은 오른쪽 자식 노드
        }
        //부모노드와 더 큰 자식노드의 키값 비교
        if(temp.key >= h->heap[child].key)
            break;
        parent = child;
        child = child *2;
    }
    h->heap[parent] = temp;
    return item;
}
//힙정렬
void heap_sort(HeapType *h,element a[]){
    //삭제 함수를 호출하여 리턴 받음
    int n = h-> heap_size;
    for (int i = n-1; i >= 0; i--) {
        a[i] = delete_max_heap(h);
    }

}
//자료구조 31p
int main() {
    element a[8] = {23, 56, 11, 9 , 56,99,27,34};
    HeapType heap;
    init(&heap);
    for(int i = 0; i < 8; i++) {
        insert_max_heap(&heap, a[i]);
    }
    element tmp = delete_max_heap(&heap);
    printf("우선순위가 가장 높은 값 %d\n", tmp.key);
   // element e[MAX_ELEMENT];
   // srand(time(NULL));
    //HeapType *heap;
   // element tmp = delete_max_heap(&heap);
   heap_sort(*h,a);
//    while (1) {
//        switch (menu_display()) {
//            case 1:
//                for (int i = 0; i < 10; i++) {
//                    //int randN = rand() % 100 +1;
//                    e[i].key = rand() % 100 + 1;
//                }
//                break;
//            case 2:
//                heap = create();
//                init(heap);
//                for (int i = 0; i < 10; i++) {
//                    insert_max_heap(heap, e[i]);
//                    print_heap(heap);
//                    printf("\n");
//                }
//                break;
//            case 3:
//                exit(0);
//    }
//    }
}