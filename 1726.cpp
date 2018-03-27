#include <stdio.h>
#include <queue>
#include <algorithm>
#include <tuple>
using namespace std;
int D[105][105][4];
int map[105][105];
int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };
typedef tuple <int, int, int> tiii;
#define EAST 0
#define WEST 1
#define SOUTH 2
#define NORTH 3
int M, N;
int st1, st2, st3;
int en1, en2, en3;
bool isOutOfBounds(int x, int y) {
	return x < 0 || x >= M || y < 0 || y >= N;
}
int main(void) {
	scanf("%d %d", &M, &N);
	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++)
			scanf("%d", &map[i][j]);
	scanf("%d %d %d", &st1, &st2, &st3);
	scanf("%d %d %d", &en1, &en2, &en3);
	st1--; st2--; st3--;  en1--; en2--; en3--;
	D[st1][st2][st3] = 1;
	queue<tiii> Q;
	Q.push({ st1,st2,st3 });
	while (!Q.empty()) {
		tiii cur = Q.front();
		Q.pop();
		int curX = get<0>(cur);
		int curY = get<1>(cur);
		int curD = get<2>(cur);
		int depth = D[curX][curY][curD];
		if (curD == EAST || curD == WEST) {
			if (D[curX][curY][SOUTH] == 0) {
				D[curX][curY][SOUTH] = depth + 1;
				Q.push({ curX,curY,SOUTH });
			}
			if (D[curX][curY][NORTH] == 0) {
				D[curX][curY][NORTH] = depth + 1;
				Q.push({ curX,curY,NORTH });
			}
		}
		else {
			if (D[curX][curY][EAST] == 0) {
				D[curX][curY][EAST] = depth + 1;
				Q.push({ curX,curY,EAST });
			}
			if (D[curX][curY][WEST] == 0) {
				D[curX][curY][WEST] = depth + 1;
				Q.push({ curX,curY,WEST });
			}
		}
		for (int k = 1; k <= 3; k++) {
			int newX = curX + dx[curD] * k;
			int newY = curY + dy[curD] * k;
			if(map)
			if (isOutOfBounds(newX, newY))
				break;
			if(D[newX][newY][curD] != 0)
				continue;
			if (map[newX][newY] == 1)
				break;
			D[newX][newY][curD] = depth + 1;
			Q.push({ newX,newY,curD });
		}
	}
	printf("%d", D[en1][en2][en3]-1);
}
