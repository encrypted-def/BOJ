#include <stdio.h>
#include <queue>
#include <algorithm>
using namespace std;
typedef pair<int, int> PAIR;
#define X first
#define Y second
int N, M;
void dfs(int map[][100], int* cheese_cnt) {
    queue<PAIR> Q;
    Q.push({ 0,0 });
    bool isVisit[100][100] = { 0, };
    while (!Q.empty()) {
        PAIR current = Q.front();
        Q.pop();
        int dx[4] = { 1,-1,0,0 };
        int dy[4] = { 0,0,1,-1 };
        for (int dir = 0; dir < 4; dir++) {
            int cand_X = current.X + dx[dir];
            int cand_Y = current.Y + dy[dir];
            if (cand_X < 0 || cand_X >= N || cand_Y < 0 || cand_Y >= M)
                continue;
            if (map[cand_X][cand_Y] == 0 && !isVisit[cand_X][cand_Y]) {
                isVisit[cand_X][cand_Y] = 1;
                Q.push({ cand_X, cand_Y });
            }
            if (map[cand_X][cand_Y] == 1 && !isVisit[cand_X][cand_Y]) {
                isVisit[cand_X][cand_Y] = 1;
                map[cand_X][cand_Y] = 0;
                (*cheese_cnt)--;
            }
        }
    }
}
int main(void){
    scanf("%d %d", &N, &M);
    int map[100][100];
    int cheese_cnt = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &map[i][j]);
            if (map[i][j])
                cheese_cnt++;
        }
    }
    int time = 0;
    int tmp = cheese_cnt;
    while (cheese_cnt > 0) {
        tmp = cheese_cnt;
        dfs(map, &cheese_cnt);
        time++;
    }
    printf("%d\n%d", time, tmp);
}
