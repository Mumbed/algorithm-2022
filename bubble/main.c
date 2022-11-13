#include <stdio.h>
#define MAX_SIZE 6
#define SWAP(x,y,temp) ((temp) = (x) ,(x)= (y) ,(y) = (temp))
void prn_sort(int list[],int n);
void bubble_sort(int list[],int n){
    int temp;
    for(int i=n-1;i>0;i--) {
        for (int j = 0; j<i; j++) {
            if(list[j] > list[j+1])
                SWAP(list[j],list[j+1],temp);
        }
        printf("%d단계",n-i);
        prn_sort(list, n);
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
    bubble_sort(list,n);
    printf("----정렬 후----\n");
    prn_sort(list,n);
    return 0;
}
