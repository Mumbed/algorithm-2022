#include <stdio.h>
#define MAX_SIZE 6
void prn_sort(int list[],int n);
void insertion_sort(int list[],int n){
    int key, j;
    for(int i=0;i<n;i++){
        key = list[i];
        for(j=i-1;j>=0 && list[j] >key; j--){
            list[j+1] = list[j];
        }
        list[j+1] = key;
        printf("%d단계:", i);
        prn_sort(list,n);
    }
}
void prn_sort(int list[],int n){
    for(int i = 0; i<n; i++)
        printf("%3d", list[i]);
    printf("\n");

}
int main() {
    int n = MAX_SIZE;
    int list[] = {5,3,8,1,2,7};
    printf("----정렬 전----\n");
    prn_sort(list, n);
    insertion_sort(list,n);
    printf("----정렬 후----\n");
    prn_sort(list,n);
    return 0;
}
