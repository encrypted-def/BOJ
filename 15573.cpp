#include <stdio.h>
#include <queue>
#include <algorithm>
using namespace std;
typedef pair<int, int> pii;
#define X first
#define Y second
int N, M, K;
int S[1003][1003];
bool isVisited[1003][1003];
int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };
bool isOutOfBounds(int x, int y) {
	return x < 0 || x >= N || y < 0 || y >= M;
}
int calc(int D) {
	int cnt = 0;
	if (N == 1 || M == 1) {
		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++)
				cnt += (S[i][j] <= D);
		return cnt;
	}
	queue<pii> Q;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			isVisited[i][j] = false;
	pii vertex[4] = { {0,0},{0,M - 1},{N - 1,0},{N - 1,M - 1} };
	for (auto v : vertex) {
		if (S[v.X][v.Y] <= D) {
			isVisited[v.X][v.Y] = true;
			Q.push({ v.X,v.Y });
		}
	}
	for (int i = 1; i < N-1; i++) {
		if (S[i][0] <= D) {
			isVisited[i][0] = true;
			Q.push({ i,0 });
		}
		if (S[i][M - 1] <= D) {
			isVisited[i][M - 1] = true;
			Q.push({ i,M - 1 });
		}
	}
	for (int j = 1; j < M - 1; j++) {
		if (S[0][j] <= D) {
			isVisited[0][j] = true;
			Q.push({ 0,j });
		}
	}
	while (!Q.empty()) {
		cnt++;
		pii cur = Q.front();
		Q.pop();
		for (int dir = 0; dir < 4; dir++) {
			int x = cur.X + dx[dir];
			int y = cur.Y + dy[dir];
			if (isOutOfBounds(x, y) || isVisited[x][y] || S[x][y] > D)
				continue;
			isVisited[x][y] = true;
			Q.push({ x,y });
		}
	}
	return cnt;
}
int main(void) {
	scanf("%d %d %d", &N, &M, &K);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			scanf("%d", &S[i][j]);
	int st = 0;
	int en = 1000000;
	while (st != en) {
		int mid = (st + en) / 2;
		if (calc(mid) < K)
			st = mid + 1;
		else
			en = mid;
	}
	printf("%d", st);
}
