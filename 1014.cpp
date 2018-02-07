#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
int dx[6] = { 1,1,0,0,-1,-1 };
int dy[6] = { 1,-1,1,-1,1,-1 };
char map[81][81];
int N, M;
#define X first
#define Y second
typedef pair<int, int> PAIR;
PAIR nxt[81][81];
bool isVisited[81][81];
bool isOutOfBounds(int x, int y) {
	return x < 0 || x >= N || y < 0 || y >= M;
}
bool bipartite_recursion(PAIR cur) {
	isVisited[cur.X][cur.Y] = true;
	for(int dir = 0; dir < 6; dir++){
		int curX = cur.X + dx[dir];
		int curY = cur.Y + dy[dir];
		if (isOutOfBounds(curX, curY) || map[curX][curY] == 'x')
			continue;
		if (nxt[curX][curY] == make_pair(0, 0) || !isVisited[nxt[curX][curY].X][nxt[curX][curY].Y] && bipartite_recursion(nxt[curX][curY])) {
			nxt[cur.X][cur.Y] = make_pair(curX, curY);
			nxt[curX][curY] = make_pair(cur.X, cur.Y);
			return true;
		}
	}
	return false;
}
void init_isVisited() {
	for (int i = 0; i < N; i++) 
		for (int j = 0; j < M; j++)
			isVisited[i][j] = false;
}
int main(void) {
	int C;
	scanf("%d", &C);
	while (C--) {
		int ans = 0;
		scanf("%d %d", &N, &M);
		for (int i = 0; i < N; i++)
			scanf("%s", map[i]);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				ans += (map[i][j] == '.');
				nxt[i][j] = make_pair( 0,0 );
			}
		}
		init_isVisited();
		for (int i = 0; i < N; i++) {
			for (int j = 1; j < M; j += 2) {
				init_isVisited();
				if (map[i][j] == '.' && bipartite_recursion({ i,j }))
					ans--;
			}
		}
		printf("%d\n", ans);
	}
}
