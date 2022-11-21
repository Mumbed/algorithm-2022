#include <stdio.h>

#define MAX_SIZE 9
#define SWAP(x,y,t) ((t)=(x), (x) = (y), (y) = (t))

int partition(int list[], int left, int right){
    int pivot, temp;
    int low, high;
    low = left;
    high = right + 1;
    pivot = list[0];

    do{
        do{
            low++;
        }while(list[low] < pivot);//피봇값보다 큰 값을 찾기위해
        do{
            high--;
        }while(list[high] > pivot);
        SWAP(list[low], list[high],temp);
    }while(low< high);
        SWAP(list[left], list[high], temp);
        return high;
}
void quick_sort(int list[], int left, int right){
    if(left < right) {
        int p = partition(list, left, right);
        quick_sort(list, left, p - 1);
        quick_sort(list, p + 1, right);
    }
}
int main() {
    int list[MAX_SIZE] = {5,3,8,4,9,1,6,2,7 };
    int n = MAX_SIZE;

    quick_sort(list,0,n-1);
}
