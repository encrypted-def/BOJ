#include <stdio.h>
char map[2300][2300];
void solve(int N, int x, int y) {
	if (N == 1) {
		map[x][y] = '*';
		return;
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (i == 1 && j == 1)
				continue;
			solve(N / 3, x + N / 3 * i, y + N / 3 * j);
		}
	}
}
int main(void) {
	int N;
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			map[i][j] = ' ';
	solve(N, 0, 0);
	for (int i = 0; i < N; i++)
		printf("%s\n", map[i]);
}
