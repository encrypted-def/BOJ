#include <stdio.h>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
int n;
typedef pair<int, int> PAIR;
#define X first
#define Y second
int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };
int area[30][30];
char map[30][30];
vector<int> adj[700];
bool isOutOfBounds(int x, int y) {
	return x < 0 || x >= n || y < 0 || y >= n;
}
int main(void) {
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%s", map[i]);
	int color_idx = 1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			queue<PAIR> Q;
			if (area[i][j] > 0)
				continue;
			area[i][j] = color_idx;
			Q.push({ i,j });
			while (!Q.empty()) {
				PAIR cur = Q.front();
				Q.pop();
				for (int dir = 0; dir < 4; dir++) {
					int nearX = cur.X + dx[dir];
					int nearY = cur.Y + dy[dir];
					if (isOutOfBounds(nearX, nearY) || area[nearX][nearY] > 0 || map[nearX][nearY] != map[cur.X][cur.Y])
						continue;
					area[nearX][nearY] = color_idx;
					Q.push({ nearX, nearY });
				}
			}
			color_idx++;
		}
	}
	if (color_idx == 2) { // 모두가 같은 색일 경우
		printf("0");
		return 0;
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int dir = 0; dir < 4; dir++) {
				int x = i + dx[dir];
				int y = j + dy[dir];
				if (isOutOfBounds(x, y) || area[i][j] == area[x][y])
					continue;
				int area1 = area[i][j];
				int area2 = area[x][y];
				if (find(adj[area1].begin(), adj[area1].end(), area2) == adj[area1].end()) // area2가 없으면
					adj[area1].push_back(area2);
				if (find(adj[area2].begin(), adj[area2].end(), area1) == adj[area2].end()) // area2가 없으면
					adj[area2].push_back(area1);
			}
		}
	}
	int ans = 8000;
	for (int st = 1; st < color_idx; st++) { // st로부터 가장 멀리 떨어진 node와의 거리가 st를 기준으로 하는 것의 최소 탭 횟수
		int dist = 0;
		vector<int> depth(color_idx);
		depth[st] = 1;
		queue<int> Q;
		Q.push(st);
		while (!Q.empty()) {
			int cur = Q.front();
			Q.pop();
			for (auto near : adj[cur]) {
				if (depth[near] > 0)
					continue;
				depth[near] = depth[cur] + 1;
				dist = max(dist, depth[near] - 1);
				Q.push(near);
			}
		}
		ans = min(ans, dist);
	}
	printf("%d", ans);
}
