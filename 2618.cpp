#include <stdio.h>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <functional>
#include <assert.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };
#define X first
#define Y second
int N,W;
pii place[1002];
pii tracking[1002][1002];
int ans[1002];
void calc(int idx, pii track) {
	if (track == make_pair(0, 0))
		return;
	pii before = tracking[track.X][track.Y];
	if (track.X == idx) {
		while (idx > track.Y)
			ans[idx--] = 1;
	}
	else {
		while (idx > track.X)
			ans[idx--] = 2;
	}
	calc(idx, before);
}
int D[1002][1002]; // D[i][j] : 경찰차1의 최종 위치가 i, 경찰차2의 최종 위치가 j일 때 이동 거리의 최솟값
int dist(pii a, pii b) {
	return abs(a.X - b.X) + abs(a.Y - b.Y);
}
int main(void) {
	scanf("%d %d", &N, &W);
	for (int i = 1; i <= W; i++)
		scanf("%d %d", &place[i].X, &place[i].Y);
	D[0][1] = dist({ N,N }, place[1]);
	D[1][0] = dist({ 1,1 }, place[1]);
	for (int i = 2; i <= W; i++) {
		D[i][i-1] = D[0][i-1]+ dist({ 1,1 }, place[i]);
		tracking[i][i - 1] = { 0,i - 1 };
		for (int j = 1; j < i - 1; j++) {
			if (D[i][i - 1] > D[j][i - 1] + dist(place[j], place[i])) {
				D[i][i - 1] = D[j][i - 1] + dist(place[j], place[i]);
				tracking[i][i - 1] = { j,i - 1 };
			}
		}
		D[i-1][i] = D[i-1][0] + dist({ N,N }, place[i]);
		tracking[i - 1][i] = { i - 1,0 };
		for (int j = 1; j < i - 1; j++) {
			if (D[i - 1][i] > D[i - 1][j] + dist(place[j], place[i])) {
				D[i - 1][i] = D[i - 1][j] + dist(place[j], place[i]);
				tracking[i - 1][i] = { i - 1,j };
			}
		}
		for (int j = 0; j < i-1; j++) {
			D[j][i] = D[j][i-1] + dist(place[i - 1], place[i]);
			D[i][j] = D[i-1][j] + dist(place[i - 1], place[i]);
			tracking[j][i] = { j,i - 1 };
			tracking[i][j] = { i-1,j};
		}
	}
	int mn = 0x7f7f7f7f;
	pii fin;
	for (int i = 0; i < W; i++) {
		if (mn > D[W][i]) {
			mn = D[W][i];
			fin = { W,i };
		}
		if (mn > D[i][W]) {
			mn = D[i][W];
			fin = { i,W };
		}
	}
	calc(W, fin);
	printf("%d\n", mn);
	for (int i = 1; i <= W; i++) {
		assert(ans[i] != 0);
		printf("%d\n", ans[i]);
	}
}
