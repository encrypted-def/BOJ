#include <stdio.h>
int main(void) {
    long long D[100][2]; // D[i][j] : i자리 수, 맨 앞에 j가 옴
    int N;
    scanf("%d", &N);
    D[1][0] = 1;
    D[1][1] = 1;
    for (int i = 2; i <= N; i++) {
        D[i][0] = D[i - 1][0] + D[i - 1][1];
        D[i][1] = D[i - 1][0];
    }
    printf("%lld", D[N][1]);
}
