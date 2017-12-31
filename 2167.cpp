#include <stdio.h>
int arr[301][301];
int D[301][301]; // D[i][j] : (1,1)부터 (i, j)까지의 합
int main(void) {
    int N, M;
    scanf("%d %d", &N, &M);
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++)
            scanf("%d", &arr[i][j]);
    }
    for (int i = 1; i <= N; i++) {
        D[i][1] = D[i - 1][1] + arr[i][1];
        for (int j = 2; j <= M; j++) {
            D[i][j] = D[i][j - 1] + D[i-1][j] + arr[i][j] - D[i-1][j-1];
        }
    }
    int K;
    scanf("%d", &K);
    while (K--) {
        int i, j, x, y;
        scanf("%d %d %d %d", &i, &j, &x, &y);
        printf("%d\n", D[x][y] - D[x][j - 1] - D[i - 1][y] + D[i - 1][j - 1]);
    }
}
