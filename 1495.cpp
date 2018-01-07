#include <stdio.h>
bool isPossible[1003][2];
int volume[102];
int main(void) {
    int N, S, M;
    scanf("%d %d %d", &N, &S, &M);
    for (int i = 0; i < N; i++)
        scanf("%d", &volume[i]);
    isPossible[S][0] = true;
    for (int i = 1; i <= N; i++) {
        for (int j = 0; j <= M; j++) {
            isPossible[j][i % 2] = false;
            if (j - volume[i-1] >= 0 && isPossible[j - volume[i-1]][1 - i % 2])
                isPossible[j][i % 2] = true;
            if (j + volume[i-1] <= M && isPossible[j + volume[i-1]][1 - i % 2])
                isPossible[j][i % 2] = true;
        }
    }
    int mx = -1;
    for (int i = M; i >= 0; i--) {
        if (isPossible[i][N % 2]) {
            mx = i;
            break;
        }
    }
    printf("%d", mx);
}
