#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 20

//허프만 트리 구조체
typedef struct TreeNode{
    int weight;             //빈도수
    char ch;                //문자열
    struct TreeNode* left;
    struct TreeNode* right;
}TreeNode;

typedef struct {
    TreeNode* ptree;
    char ch;
    int key;
}element;
//힙트리 구조체
typedef struct{
    element heap[MAX_ELEMENT];
    int heap_size;
}HeapType;

HeapType * create(){
    HeapType * temp = (HeapType*) malloc(sizeof(HeapType));
    return temp;
}

void init(HeapType * h){
    h->heap_size = 0;
}

//허프만 트리 생성
void insert_min_heap(HeapType *h,element item){
    int i;
    i = ++(h->heap_size);
    while((i != 1) && (item.key < h->heap[i/2].key)){
        h ->heap[i] = h->heap[i/2];
        i /=2;
    }
    h->heap[i] = item;
}
//허프만 트리 생성을 위하 ㄴ메모리 할당
TreeNode *make_tree(TreeNode *left,TreeNode *right){
    TreeNode *node = (TreeNode*)malloc(sizeof(TreeNode));
    node->left = left; node->right = right;
    return node;
}

element delete_min_heap(HeapType *h){
    int parent, child;
    element item, temp;
    item = h->heap[1];
    temp = h->heap[(h->heap_size)--];
    parent = 1;
    child = 2;

    while(child <= h->heap_size){
        if((child < h->heap_size) && h->heap[child].key > h->heap[child + 1].key)
            child++;
        if(temp.key < h->heap[child].key)
            break;
        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }
    h->heap[parent] =temp;
    return item;
}
//허프만 코드 생성
void huffman_tree(int freq[],char ch_list[],int n){
    TreeNode* node, *x;
    HeapType *heap;

    heap = create();

    init(heap);
    element e;

    for(int i= 0 ;i <n;i++){
        node = make_tree(NULL,NULL);
        e.ch = ch_list[i];
        e.key = freq[i];
        e.ptree = node;
        insert_min_heap(heap,e);
    }
    element e1,e2;
    for(int i=0 ;i < n-1 ;i++){
        e1 = delete_min_heap(heap);
        e2 = delete_min_heap(heap);
        x = make_tree(e1.ptree,e2.ptree);
        e.key = x->weight = e1.key + e2.key;
        e.ptree = x;
        printf("%d + %d -> %d\n",e1.key,e2.key,e.key);
        insert_min_heap(heap,e);
    }
    e = delete_min_heap(heap);
    int top = 0;
    print_codes(e.ptree,codes, top);
}


int main(){
        char ch_list[] = { "s","i","n","t","e" };
        int freq[] = {4,6,8,12,15};

        huffman_tree(freq, ch_list,5);

};
