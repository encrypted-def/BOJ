#include <stdio.h>
#include <algorithm>
#include <tuple>
using namespace std;
#define BAMBOO tuple<int, int, int> // tuple<h, i, j> => (i, j) 대나무의 길이는 h
int forest[501][501]; // 대나무 길이 저장
int D[501][501]; // D[i][j] : (i, j) 대나무에서 시작했을 때 최대로 생존할 수 있는 날의 수
BAMBOO tmp[250001]; // 대나무를 길이순으로 sort해서 tmp에 저장, 긴 것부터 D[i][j]를 구해나갈 것임
int main(void) {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &forest[i][j]);
            tmp[i*n + j] = make_tuple( forest[i][j], i, j );
        }
    }
    int mx = 0;
    sort(tmp, tmp + n*n);
    int dx[4] = { 1, -1, 0, 0 };
    int dy[4] = { 0, 0, 1, -1 };
    for (int i = n*n - 1; i >= 0; i--) {
        int x = get<1>(tmp[i]);
        int y = get<2>(tmp[i]);
        for (int dir = 0; dir < 4; dir++) {
            int x_new = x + dx[dir];
            int y_new = y + dy[dir];
            if (x_new < 0 || x_new >= n || y_new < 0 || y_new >= n || forest[x][y] >= forest[x_new][y_new])
                continue;
            D[x][y] = max(D[x][y], D[x_new][y_new]+1);
            mx = max(D[x][y], mx);
        }
    }
    printf("%d", mx+1);
}
