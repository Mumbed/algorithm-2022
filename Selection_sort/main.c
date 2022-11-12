// 5 3 8 1 2 7
//selection 정렬  , 삽입정렬 , 버블 정렬  (성능 O(n2)
//퀵 정렬 (성능 O(log2n))

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_SIZE 10
//매크로 함수 1 치환 : 전처리기 2 컴파일러 계산
//#define SQ(x) ((x)*(x))
#define SWAP(x,y,t) ((t) = (x), (x) = (y), (y) = (t))

int list[MAX_SIZE];
void prn_sort(int list[], int n);
void selection_sort(int list[], int n) {
    int i, j, least, temp;
    for (i = 0; i < n - 1; i++) {
        least = i;
        for (j = i + 1; j < n; j++)
            if (list[j] < list[least])
                least = j;

            SWAP(list[i], list[least], temp);
            printf("%d단계",i);
            prn_sort(list, n);

    }
}
void prn_sort(int list[], int n){
    for(int i = 0; i < n; i++) {
        printf("%3d", list[i]);
    }
    printf("\n");
}
int main(){
    int i,n;
    n = MAX_SIZE;
    srand(time(NULL));
    for(i = 0; i < n; i++)
        list[i] = rand() % 100;
    printf("---정렬 전 데이터---\n");
    prn_sort(list, n);
    selection_sort(list,n);
    printf("---정렬 후 데이터---\n");
    prn_sort(list, n);
    printf("\n");
}