#include <stdio.h>
#include <algorithm>
#include <queue>
using namespace std;
#define PAIR pair<int, int>
#define X first
#define Y second
int height[100][100];
int isSafe[100][100];
int N;
int dx[4] = { 1, -1, 0, 0 };
int dy[4] = { 0, 0, 1, -1 };
int calculate() {
    int cnt = 0;
 
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (isSafe[i][j]) { // 이제 (i, j)와 연결되어있는 모든 땅을 찾아 0으로 만들 것임
                cnt++;
                isSafe[i][j] = false;
                queue<PAIR > Q;
                Q.push(make_pair(i, j));
                while (!Q.empty()){
                    PAIR cur = Q.front();
                    Q.pop();
                    for (int dir = 0; dir < 4; dir++) {
                        if (cur.X + dx[dir] < 0 || cur.X + dx[dir] >= N || cur.Y + dy[dir] < 0 || cur.Y + dy[dir] >= N)
                            continue;
                        if (isSafe[cur.X + dx[dir]][cur.Y + dy[dir]]) {
                            Q.push(make_pair(cur.X + dx[dir], cur.Y + dy[dir]));
                            isSafe[cur.X + dx[dir]][cur.Y + dy[dir]] = false;
                        }
                    }
                }
            }
        }
    }
    return cnt;
}
int main(void) {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            scanf("%d", &height[i][j]);
    }
    int mx = 1;
    for (int h = 1; h < 100; h++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                isSafe[i][j] = (height[i][j] > h);                
            }
        }
        mx = max(mx, calculate());
 
    }
 
    printf("%d", mx);
}
