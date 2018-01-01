#include <stdio.h>
#include <algorithm>
#include <queue>
using namespace std;
#define X first
#define Y second
#define PAIR pair<int, int>
int main(void) {
    int T;
    scanf("%d", &T);
    int dx[4] = { 1, -1, 0, 0 };
    int dy[4] = { 0 ,0 ,1 ,-1 };
    while (T--) {
        int M, N, K;
        scanf("%d %d %d", &M, &N, &K);
        int map[50][50] = { 0, }; // 0 : 배추 없음 1 : 배추 있음, 아직 방문 안함 2 : 배추 있음, 방문함
        for (int i = 0; i < K; i++) {
            int x, y;
            scanf("%d %d", &x, &y);
            map[x][y] = 1;
        }
        int num = 0;
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                if (map[i][j] == 1) { // 아직 방문하지 않았고 배추가 있는 곳을 찾았다면
                    num++; // 벌레를 한 마리 둠
                    map[i][j] = 2;
                    queue<PAIR> Q;
                    Q.push(make_pair(i, j));
                    while (!Q.empty()) {
                        PAIR t = Q.front();
                        Q.pop();
                        for (int dir = 0; dir < 4; dir++) {
                            if (t.X + dx[dir] < 0 || t.X + dx[dir] >= M || t.Y + dy[dir] < 0 || t.Y + dy[dir] >= N)
                                continue;
                            if (map[t.X + dx[dir]][t.Y + dy[dir]] == 1) {
                                Q.push(make_pair(t.X + dx[dir], t.Y + dy[dir]));
                                map[t.X + dx[dir]][t.Y + dy[dir]] = 2;
                            }
                        }
                    }
                }
            }
        }
        printf("%d\n", num);
    }
}
