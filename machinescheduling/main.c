#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 20
typedef struct{
    int id;
    int avail;
} element;

typedef struct {
    element heap[MAX_ELEMENT];
    int heap_size;
}HeapType;

HeapType* create(){
    return (HeapType*) malloc(sizeof(HeapType));
}
void init(HeapType* h){
    h->heap_size = 0;
}

void insert_min_heap(HeapType* h, element item){
    int i = ++(h->heap_size);
    while((i != 1) && (item.avail < h->heap[i/2].avail)){
        h->heap[i] = h->heap[i/2];
        i /=2;
    }
    h->heap[i] = item;
}
element delete_min_heap(HeapType* h){
    int parent, child;
    element item, temp;
    item = h->heap[1];
    temp = h->heap[(h->heap_size)--];
    parent = 1;
    child = 2;
    while(child <= h->heap_size ) {
        if((child < h->heap_size) && (h->heap[child].avail) > h->heap[child +1].avail)
        child++;
        if (temp.avail < h->heap[child].avail)
            break;
        h->heap[parent] = h->heap[child];
        parent = child;
        child *=2;
    }
    h->heap[parent] = temp;
    return item;
}
#define JOBS 7
#define MACHINES 3
int main() {
    int jobs[JOBS] = {8,7,6,5,3,2,2};
    element m = {0,0};
    HeapType* heap;
    heap = create();
    init(heap);
    for(int i = 0; i <MACHINES ; i++){
        m.id = i + 1;
        m.avail = 0; //기계가 사용하게 되는 값
        insert_min_heap(heap,m);
    }
    for(int i = 0; i <JOBS ; i++){
        m = delete_min_heap(heap);
        printf("JOB %d를 시간 %d부터 시간 %d까지 machine %d번에 할당함\n",i, m.avail, m.avail +jobs[i]-1,m.id);
        m.avail += jobs[i];
        insert_min_heap(heap,m);// 0 0 7 1 // 1 0 6 2 // 2 0 5 3// 3 6 10 3// 4 7 9 2//5 8 9 1//6 11 11 3
    }
    free(heap);

    return 0;
}
