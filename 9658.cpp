#include <stdio.h>
int D[1003]; // D[i] = 1 : 돌이 i개 있을 때 선수가 이김
int main(void) {
    D[0] = 1;
    D[1] = 0;
    D[2] = 1;
    D[3] = 0;
 
    for (int i = 4; i <= 1000; i++) {
        if (D[i - 1] == 1 && D[i - 3] == 1 && D[i - 4] == 1)
            D[i] = 0;
        else
            D[i] = 1;
    }
    int N;
    scanf("%d", &N);
    if (D[N] == 1)
        printf("SK");
    else
        printf("CY");
    
}
