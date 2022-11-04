#include <stdio.h>
#include <stdlib.h>

void gugudan_n(){
    int n;
    scanf("%d",&n);
    for(int i=1; i<=9; i++){
        printf("%d * %d = %d\n",n,i,n*i);
    }
}

void gugudan_all(){
    for(int i=1;i<=9;i++){
        for(int j=1;j<=9;j++){
            printf("%d * %d = %d\n",i,j,j*i);
        }
    }
}

int menu_display(){
    int menu;
    printf("**구구단 출력**\n");
    printf("1. 원하는 단만 출력\n");
    printf("2. 전체 구구단 출력\n");
    printf("3. 프로그램 종료\n");
    scanf("%d",&menu);
    return menu;
}

int main(void) {
    while(1) {
            switch (menu_display()) {
                case 1:
                    gugudan_n();
                    break;
                case 2:
                    gugudan_all();
                    break;
                case 3:
                    exit(0);
            }
        }
}