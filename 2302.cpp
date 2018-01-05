#include <stdio.h>
typedef long long LL;
int main(void) {
    LL D[42]; // D[i] : VIP석이 없는 경우 i명을 배치할 수 있는 경우의 수
    D[0] = 1;
    D[1] = 1;
    D[2] = 2;
    for (int i = 3; i <= 40; i++)
        D[i] = D[i - 1] + D[i - 2];
    int N, M;
    scanf("%d %d", &N, &M);
    int fix[42];
    for (int i = 0; i < M; i++)
        scanf("%d", &fix[i]);
    if (M == 0) {
        printf("%lld", D[N]);
        return 0;
    }
    LL val = 1;
    val *= D[fix[0] - 1];
    for (int i = 1; i < M; i++)
        val *= D[fix[i] - fix[i - 1] - 1];
    val *= D[N - fix[M - 1]];
    printf("%lld", val);
}
