#include <stdio.h>
#include <algorithm>
using namespace std;
int D[410][410][410]; // D[a][b][c] : 윗칸의 수 a개, 밑칸의 수 b개를 2*c개의 칸에 배치했을 때 최댓값
int box1[401];
int box2[401];
int idx1 = 0;
int idx2 = 0;
int max3(int v1, int v2, int v3) {
    return max(max(v1, v2), v3);
}
int main(void) {
    int N;
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        int tmp;
        scanf("%d", &tmp);
        if (tmp != 0)
            box1[idx1++] = tmp;
    }
    for (int i = 0; i < N; i++) {
        int tmp;
        scanf("%d", &tmp);
        if (tmp != 0)
            box2[idx2++] = tmp;
    }
 
    for (int c = 1; c <= N; c++) {
        for (int a = 1; a <= min(idx1, c); a++) {
            for (int b = 1; b <= min(idx2, c); b++) {
                if (b > c - 1 && a > c - 1)
                    D[a][b][c] = D[a - 1][b - 1][c - 1] + box1[a - 1] * box2[b - 1];
                else if (b > c - 1)
                    D[a][b][c] = max(D[a][b - 1][c - 1], D[a - 1][b - 1][c - 1] + box1[a - 1] * box2[b - 1]);
                else if (a > c - 1)
                    D[a][b][c] = max(D[a - 1][b][c - 1], D[a - 1][b - 1][c - 1] + box1[a - 1] * box2[b - 1]);
                else
                    D[a][b][c] = max3(D[a - 1][b][c - 1], D[a][b - 1][c - 1], D[a - 1][b - 1][c - 1] + box1[a - 1] * box2[b - 1]);
 
            }
        }
    }
    printf("%d", D[idx1][idx2][N]);
}
