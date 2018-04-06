#include <stdio.h>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <functional>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define X first
#define Y second
int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };
int N, S;
char map[802][802];
int dist_bee[802][802];
int dist_bear[802][802];
pii bear, house;
bool isOutOfBounds(int x, int y) {
	return x < 0 || x >= N || y < 0 || y >= N;
}
bool isPossible(int time) {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			dist_bear[i][j] = -1;		
	queue<pii> Q;
	Q.push(bear);
	dist_bear[bear.X][bear.Y] = 0;
	if (time >= dist_bee[bear.X][bear.Y])
		return false;
	while (!Q.empty()) {
		pii cur = Q.front();
		Q.pop();
		for (int dir = 0; dir < 4; dir++) {
			int nX = cur.X + dx[dir];
			int nY = cur.Y + dy[dir];
			if (make_pair( nX, nY ) == house)
				return true;
			if (isOutOfBounds(nX, nY) || (map[nX][nY] != 'G' && map[nX][nY] != 'M') || dist_bear[nX][nY] != -1)
				continue;
			if (time+(dist_bear[cur.X][cur.Y]+1) / S >= dist_bee[nX][nY])
				continue;
			dist_bear[nX][nY] = dist_bear[cur.X][cur.Y] + 1;
			Q.push({ nX, nY });
		}
	}
	return false;
}
int main(void) {
	scanf("%d %d", &N, &S);
	for (int i = 0; i < N; i++)
		scanf("%s", map[i]);
	queue<pii> Q;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			dist_bee[i][j] = -1;
			if (map[i][j] == 'M')
				bear = { i,j };
			else if (map[i][j] == 'D')
				house = { i,j };
			else if (map[i][j] == 'H') {
				Q.push({ i,j });
				dist_bee[i][j] = 0;
			}
		}
	}
	while (!Q.empty()) {
		pii cur = Q.front();
		Q.pop();
		for (int dir = 0; dir < 4; dir++) {
			int nX = cur.X + dx[dir];
			int nY = cur.Y + dy[dir];
			if (isOutOfBounds(nX, nY) || (map[nX][nY] != 'G' && map[nX][nY] != 'M') || dist_bee[nX][nY] != -1)
				continue;
			Q.push({ nX, nY });
			dist_bee[nX][nY] = dist_bee[cur.X][cur.Y] + 1;
		}
	}
	if (!isPossible(0)) {
		printf("-1");
		return 0;
	}
	int st = 0;
	int en = 2*N * N+1;
	while (st < en) {
		int mid = (st + en+1) / 2;
		if (isPossible(mid)) {
			st = mid;
		}
		else
			en = mid - 1;
	}
	printf("%d", st);
}
