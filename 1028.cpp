#include <stdio.h>
#include <algorithm>
using namespace std;
char map[770][770];
int R, C;
int D1[770][770]; // 북동쪽 방향으로 몇개까지 이어지는가
int D2[770][770]; // 남동
int D3[770][770]; // 남서
int D4[770][770]; // 북서
bool isOutOfBounds(int r, int c) {
	return r < 0 || r >= R || c < 0 || c >= C;
}

int main(void) {
	scanf("%d %d", &R, &C);
	for (int i = 0; i < R; i++)
		scanf("%s", map[i]);
	for (int d = 0; d <= R + C - 2; d++) { // (r, c)에서 r+c = d인 애들을 살펴볼 예정
		for (int c = 0; c < C; c++) {
			int r = d - c;
			if (isOutOfBounds(r, c))
				continue;
			if (isOutOfBounds(r + 1, c - 1))
				D3[r][c] = (map[r][c] == '1');
			else
				D3[r][c] = (map[r][c] == '1') * (D3[r + 1][c - 1] + 1);
		}
		for (int r = 0; r < R; r++) {
			int c = d - r;
			if (isOutOfBounds(r, c))
				continue;
			if (isOutOfBounds(r - 1, c + 1))
				D1[r][c] = (map[r][c] == '1');
			else
				D1[r][c] = (map[r][c] == '1') * (D1[r - 1][c + 1] + 1);
		}
	}
	for (int d = 1-C; d <= R-1; d++) { // (r, c)에서 r-c = d인 애들을 살펴볼 예정
		for (int r = 0; r < R; r++) {
			int c = r - d;
			if (isOutOfBounds(r, c))
				continue;
			if (isOutOfBounds(r - 1, c - 1))
				D4[r][c] = (map[r][c] == '1');
			else
				D4[r][c] = (map[r][c] == '1') * (D4[r - 1][c - 1] + 1);
		}
		for (int r = R-1; r >= 0 ; r--) {
			int c = r - d;
			if (isOutOfBounds(r, c))
				continue;
			if (isOutOfBounds(r + 1, c + 1))
				D2[r][c] = (map[r][c] == '1');
			else
				D2[r][c] = (map[r][c] == '1') * (D2[r + 1][c + 1] + 1);
		}
	}
	int mx = 0;
	for (int r = 0; r < R; r++) {
		for (int c = 0; c < C; c++) { // 마름모의 왼쪽 꼭짓점을 (r, c)로 둠
			int mx_side = min(D1[r][c], D2[r][c]);
			if (mx_side < mx)
				continue;
			for (int sz = mx_side; sz >= 1; sz--) {
				if (c + 2 * (sz - 1) >= C)
					continue;
				if (sz < mx)
					break;
				if (min(D3[r][c + 2 * (sz - 1)], D4[r][c + 2 * (sz - 1)]) >= sz) {
					mx = max(mx, sz);
					break;
				}
			}
		}
	}
	printf("%d", mx);
}
