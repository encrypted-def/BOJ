#include <stdio.h>
typedef long long LL;
int board[103][103];
int N;
LL D[103][103]; // D[i][j] : (i, j)칸까지 도달하는 경우의 수
int main(void) {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) 
        for (int j = 0; j < N; j++)
            scanf("%lld", &board[i][j]);
    D[0][0] = 1;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j] == 0)
                continue;
            if (i + board[i][j] < N)
                D[i + board[i][j]][j] += D[i][j];
            if (j + board[i][j] < N)
                D[i][j + board[i][j]] += D[i][j];
        }
    }
    printf("%lld", D[N - 1][N - 1]);
}
