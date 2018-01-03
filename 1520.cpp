#include <stdio.h>
#include <algorithm>
#include <functional>
using namespace std;
typedef pair<int, int> PAIR;
#define S second
#define F first
int map[501][501];
int D[501][501]; // D[i][j] : [0][0] to [i][j]의 경로의 수
pair<int, PAIR> height[250001];
int M, N;
int main(void) {
    //freopen("input.txt", "r", stdin);
    scanf("%d %d", &M, &N);
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &map[i][j]);
            height[i*N + j] = make_pair(map[i][j], make_pair(i, j));
        }
    }
    sort(height, height + M*N, greater<pair<int, PAIR> >());
    D[0][0] = 1;
    int dx[4] = { 1, -1, 0, 0 };
    int dy[4] = { 0, 0, 1, -1 };
    for (int i = 0; i < M*N; i++) {
        int x = height[i].S.F;
        int y = height[i].S.S;
        for (int dir = 0; dir < 4; dir++) {
            if (x + dx[dir] < 0 || x + dx[dir] >= M || y + dy[dir] < 0 || y + dy[dir] >= N)
                continue;
            if (map[x][y] >= map[x + dx[dir]][y + dy[dir]])
                continue;
            D[x][y] += D[x + dx[dir]][y + dy[dir]];
        }
    }
    printf("%d", D[M - 1][N - 1]);
}
