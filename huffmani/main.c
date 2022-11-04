#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 100

typedef struct TreeNode {
    int weight;
    char ch;
    struct TreeNode *left;
    struct TreeNode *right;
}TreeNode;

typedef struct element{
    TreeNode *ptree;
    int item;
    int key;
}element;

typedef struct {
    element heap[MAX_ELEMENT];
    int heap_size;
} HeapType;

HeapType* create(){
    return (HeapType*) malloc(sizeof(HeapType));
}
void init(HeapType *h){
    h->heap_size = 0;
}

