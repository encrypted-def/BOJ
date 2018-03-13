#include <stdio.h>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;
typedef pair<int, int> pii;
#define X first
#define Y second
#define SPACE 0
#define WALL 1
#define VIRUS 2
int map[10][10];
int N, M;
int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };
bool isOutOfBounds(int x, int y) {
	return x < 0 || x >= N || y < 0 || y >= M;
}
bool isVisited[10][10];
int calc_safe(void) {
	int cnt = 0;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			isVisited[i][j] = false;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (isVisited[i][j])
				continue;
			bool isInfected = false;
			if (map[i][j] == WALL)
				continue;
			else {
				if (map[i][j] == VIRUS)
					isInfected = true;
				queue<pii> Q;
				Q.push({ i,j });
				isVisited[i][j] = true;
				int area = 0;
				while (!Q.empty()) {
					area++;
					pii cur = Q.front();
					Q.pop();
					for (int dir = 0; dir < 4; dir++) {
						int x = cur.X + dx[dir];
						int y = cur.Y + dy[dir];
						if (isOutOfBounds(x, y) || map[x][y] == WALL || isVisited[x][y])
							continue;
						Q.push({ x,y });
						isVisited[x][y] = true;
						if (map[x][y] == VIRUS)
							isInfected = true;
					}
				}
				if (!isInfected)
					cnt += area;
			}
		}
	}
	return cnt;
}
int main(void) {
	scanf("%d %d", &N, &M);
	vector<pii> space;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d", &map[i][j]);
			if (map[i][j] == SPACE)
				space.push_back({ i,j });
		}
	}
	int mx = 0;
	int len = space.size();
	for (int s1 = 0; s1 < len; s1++) {
		map[space[s1].X][space[s1].Y] = WALL;
		for (int s2 = s1 + 1; s2 < len; s2++) {
			map[space[s2].X][space[s2].Y] = WALL;
			for (int s3 = s2 + 1; s3 < len; s3++) {
				map[space[s3].X][space[s3].Y] = WALL;
				mx = max(mx, calc_safe());
				map[space[s3].X][space[s3].Y] = SPACE;
			}
			map[space[s2].X][space[s2].Y] = SPACE;
		}
		map[space[s1].X][space[s1].Y] = SPACE;
	}
	printf("%d", mx);
}
