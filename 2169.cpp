#include <stdio.h>
#include <algorithm>
using namespace std;
int arr[1004][1004];
int D[1004][1004][3]; // D[i][j][dir] : (1,1)부터 (i, j)까지 탐사할 떄 최대 가치.
                      //dir은 (i,j)로 도착하기 직전의 로봇의 위치(0 : 왼쪽, 1 : 오른쪽, 2 : 아랫쪽)
int N, M;
int max3(int a, int b, int c) {
    return max(max(a, b), c);
}
bool isInBounds(int x, int y) {
    return 1 <= x && x <= N && 1 <= y && y <= N;
}
int main(void) {
    scanf("%d %d", &N, &M);
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= M; j++)
            scanf("%d", &arr[i][j]);
    if (N == 1 && M == 1) {
        printf("%d", arr[1][1]);
        return 0;
    }
    D[1][1][0] = arr[1][1];
    D[1][1][1] = arr[1][1];
    D[1][1][2] = arr[1][1];
    for (int i = 1; i <= N; i++) {        
        if (i != 1)
            D[i][1][0] = -1e9; // (i,1) 칸의 경우 왼쪽에서 오는 것은 불가능하므로
        D[i][M][1] = -1e9; // (i,M) 칸의 경우 오른쪽에서 오는 것은 불가능하므로
        
        for (int j = 1; j <= M; j++) { // D[i][j][2] 갱신
            if (i == 1) {
                D[i][j][2] = -1e9;
                D[1][1][2] = arr[1][1];
                continue;
            }
            D[i][j][2] = max3(D[i-1][j][0], D[i-1][j][1], D[i-1][j][2]) + arr[i][j];
        }
        for (int j = 2; j <= M; j++) // D[i][j][0] 갱신
            D[i][j][0] = max(D[i][j - 1][0], D[i][j - 1][2]) + arr[i][j];
        for (int j = M - 1; j >= 0; j--) { // D[i][j][1] 갱신
            if (i == 1) {
                D[i][j][1] = -1e9;
                D[1][1][2] = arr[1][1];
                continue;
            }
            D[i][j][1] = max(D[i][j + 1][1], D[i][j + 1][2]) + arr[i][j];
        }
    }
    printf("%d", max3(D[N][M][0], D[N][M][1], D[N][M][2]));
}
