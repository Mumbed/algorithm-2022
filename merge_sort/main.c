#include <stdio.h>
#define  MAX_SIZE 8

int Sorted [MAX_SIZE];
void prn_sort(int list[],int n){
    for(int i=0;i<n;i++)
        printf("%3d ",list[i]);
    printf("\n");
}
void merge(int list[], int left, int mid,int right){
    int i,j,k,l;
    i = left;
    j = mid+1;
    k = left;
    while( i <= mid && j <= right){
        if(list[i] <= list[j]){
            Sorted[k++] = list[i++];
        }
        else
            Sorted[k++] = list[j++];
    }
    if (i > mid)
        for( l = j; l <= right; l++ )
            Sorted[k++] = list[l];
    else
        for( l = i; l <= mid; l++ )
            Sorted[k++] = list[i];
    for(l = left; l <= right; l++){
        list[l] = Sorted[l];
    }
}

void merge_sort(int list[], int left, int right){
    int mid;
    if(left < right){
        mid = (left +right) / 2;
        merge_sort(list, left, mid);
        merge_sort(list, mid +1, right);
        merge(list,left,mid,right);
    }
}
int main() {
    int list[] = {27,10,12,20,25,13,15,22};

    merge_sort(list, 0, 7);
    prn_sort(list, 8);
}
