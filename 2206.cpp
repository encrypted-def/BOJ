#include <stdio.h>
#include <queue>
#include <algorithm>
using namespace std;
typedef pair<int, int> PAIR;
#define X first
#define Y second
char map[1004][1004];
int N, M;
int dist1[1004][1004]; // (0,0)으로부터의 거리
int dist2[1004][1004]; // (N-1,M-1)으로부터의 거리
int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };
bool IsOutOfBounds(int x, int y) {
	return x < 0 || x >= N || y < 0 || y >= M;
}
int main(void) {
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++)
		scanf("%s", map[i]);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			dist1[i][j] = dist2[i][j] = -1; // -1(unreachable)로 초기화
	// dist1 먼저
	queue<PAIR> Q;
	Q.push({ 0,0 });
	dist1[0][0] = 1;
	while (!Q.empty()) {
		PAIR cur = Q.front();
		Q.pop();
		for (int dir = 0; dir < 4; dir++) {
			int x = cur.X + dx[dir];
			int y = cur.Y + dy[dir];
			if (IsOutOfBounds(x, y) || map[x][y] == '1' || dist1[x][y] != -1)
				continue;
			dist1[x][y] = dist1[cur.X][cur.Y] + 1;
			Q.push({ x,y });
		}
	}
	Q.push({ N - 1, M - 1 });
	dist2[N - 1][M - 1] = 1;
	while (!Q.empty()) {
		PAIR cur = Q.front();
		Q.pop();
		for (int dir = 0; dir < 4; dir++) {
			int x = cur.X + dx[dir];
			int y = cur.Y + dy[dir];
			if (IsOutOfBounds(x, y) || map[x][y] == '1' || dist2[x][y] != -1)
				continue;
			dist2[x][y] = dist2[cur.X][cur.Y] + 1;
			Q.push({ x,y });
		}
	}
	int min_dist = 0x7fffff;
	if (dist2[0][0] >= 0) // (0, 0) to (N-1, M-1)의 경로가 있으면
		min_dist = dist2[0][0]; // 일단 갱신해둠
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (map[i][j] == 0)
				continue;
			// 각 벽들에 대해 사방을 살펴보면서 dist1, dist2의 합의 최소를 구할 것임
			int min_dist1 = 0x7fffff;
			int min_dist2 = 0x7fffff;
			for (int dir = 0; dir < 4; dir++) {
				int x = i + dx[dir];
				int y = j + dy[dir];
				if (IsOutOfBounds(x, y))
					continue;
				if (dist1[x][y] >= 0)
					min_dist1 = min(min_dist1, dist1[x][y]);
				if (dist2[x][y] >= 0)
					min_dist2 = min(min_dist2, dist2[x][y]);
			}
			min_dist = min(min_dist, min_dist1 + min_dist2+1);
		}
	}
	if (min_dist == 0x7fffff)
		printf("-1");
	else
		printf("%d", min_dist);
	return 0;
}
