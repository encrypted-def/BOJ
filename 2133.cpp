#include <stdio.h>
int main(void){
    int D1[40] = {0, };
    int D2[40] = {0, };
    D1[0] = 1;
    D1[2] = 3;
    D2[1] = 1;
    for(int i = 1; i <= 15; i++){
        D1[2*i] = 2*D2[2*i-1] + D1[2*i-2];
        D2[2*i+1] = D1[2*i] + D2[2*i-1];
    }
    D1[0] = 0;
    int n;
    scanf("%d", &n);
    printf("%d", D1[n]);
}
