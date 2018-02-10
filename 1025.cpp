#include <stdio.h>
#include <math.h>
#include <algorithm>
using namespace std;
char map[10][10];
int N, M;
bool isSquare(int x) {
	int t = (int)sqrt(x);
	for (int i = t - 2; i <= t + 2; i++)
		if (i*i == x) return true;
	return false;
}
bool isOutOfBounds(int x, int y) {
	return x < 0 || x >= N || y < 0 || y >= M;
}
int main(void) {
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++)
		scanf("%s", map[i]);
	int ans = -1;
	for (int x = 0; x < N; x++) {
		for (int y = 0; y < M; y++) {
			for (int dx = -N; dx < N; dx++) {
				for (int dy = -M; dy < M; dy++) {
					int val = 0;
					if (dx == 0 && dy == 0)
						continue;
					int curX = x;
					int curY = y;
					while (!isOutOfBounds(curX, curY)) {
						val = 10 * val + (map[curX][curY]-'0');
						if (isSquare(val))
							ans = max(ans, val);
						curX += dx;
						curY += dy;
					}
				}
			}
		}
	}
	printf("%d", ans);
}
