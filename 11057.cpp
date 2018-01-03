#include <stdio.h>
#define MOD 10007
int D[1006][10];
int main(void){
    int N;
    scanf("%d", &N);
    for(int i = 0; i < 10; i++)
        D[1][i] = 1;
    for(int i = 2; i <= N; i++){
        for(int j = 0; j < 10; j++){
            for(int k = 0; k <= j; k++)
                D[i][j] = (D[i][j] + D[i-1][k]) % MOD;
        }
    }
    int ans = 0;
    for(int i = 0; i < 10; i++)
        ans = (ans + D[N][i]) % MOD;
    printf("%d", ans);
}
