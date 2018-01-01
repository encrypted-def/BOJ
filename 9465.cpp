#include <stdio.h>
#include <algorithm>
using namespace std;
int D[100000][2]; // D[i][0] : 0~i-1열 전체 + i열 0행에 대해 최댓값, D[i][1] : 0~i-1열 전체 + i열 1행에 대해 최댓값
int sticker[100000][2];
int main(void) {
    int T;
    scanf("%d", &T);
    while (T--) {
        int N;
        scanf("%d", &N);
        for (int i = 0; i < N; i++)
            scanf("%d", &sticker[i][0]);
        for (int i = 0; i < N; i++)
            scanf("%d", &sticker[i][1]);
        D[0][0] = sticker[0][0];
        D[0][1] = sticker[0][1];
        for (int i = 1; i < N; i++) {
            D[i][0] = max(sticker[i][0] + D[i - 1][1], D[i - 1][0]);
            D[i][1] = max(sticker[i][1] + D[i - 1][0], D[i - 1][1]);
        }
        printf("%d\n", max(D[N - 1][0], D[N - 1][1]));
    }
}
