#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_ELEMENT 11

typedef struct {
    int key;
}element;



typedef struct
{
    element heap[MAX_ELEMENT];
    int heap_size;

}HeapType;


HeapType* create() {

    HeapType* temp = (HeapType*)malloc(sizeof(HeapType));
    return temp;
}


void init(HeapType* h) {
    h->heap_size = 0;

}


void insert_max_heap(HeapType* h, element item) {
    int i = ++(h->heap_size);
    //조건- 새로 들어온 값이 부모노드보다 크다면 교환
    while ((i != 1) && item.key > h->heap[i / 2].key) {
        h->heap[i] = h->heap[i / 2];
        i = i / 2;
    }
    h->heap[i] = item;
}





void pirntfHype(HeapType* h) {


    for (int i = 1; i <= h->heap_size; i++) {

        printf("%d \n",h->heap[i]);
        printf("\n");
    }
}

int main()
{
    element e1[MAX_ELEMENT];
    srand(time(NULL));
    for (int i = 0; i < 10; i++) {
        element num = { rand() % 100 + 1 };
        e1[i] = num;

    }


    HeapType* heap;
    heap = create();
    init(heap);
    insert_max_heap(heap, e1[0]);
    insert_max_heap(heap, e1[1]);
    insert_max_heap(heap, e1[2]);
    insert_max_heap(heap, e1[3]);
    insert_max_heap(heap, e1[4]);
    insert_max_heap(heap, e1[5]);
    insert_max_heap(heap, e1[6]);
    insert_max_heap(heap, e1[7]);
    insert_max_heap(heap, e1[8]);
    insert_max_heap(heap, e1[9]);
    pirntfHype(heap);

}