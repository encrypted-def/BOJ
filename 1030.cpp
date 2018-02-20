#include <stdio.h>
#include <algorithm>
using namespace std;
char ans[101][101];
int s, N, K, R1, R2, C1, C2;
int pow(int n, int a) {
	int val = 1;
	while (a--)
		val *= n;
	return val;
}
int isBlackSection(int i) {
	return !((i < (N - K) / 2) || ((N - 1 - i) < (N - K) / 2));
}
int isContainsRange(int r1, int r2, int c1, int c2) {
	if (r1 > R2 || r2 < R1)
		return false;
	if (c1 > C2 || c2 < C1)
		return false;
	return true;
}
void solve(int x, int y, int time, int color) {
	int p = pow(N, s - time);
	if (!isContainsRange(x*p, x*p + p - 1, y*p, y*p + p - 1))
		return;
	if (time == s) {
		ans[x-R1][y-C1] = color + '0';
		return;
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int new_color;
			if (color == 1)
				new_color = 1;
			else
				new_color = (isBlackSection(i) && isBlackSection(j));
			solve(x*N + i, y*N + j, time + 1, new_color);
		}
	}

}
int main(void) {
	scanf("%d %d %d %d %d %d %d", &s, &N, &K, &R1, &R2, &C1, &C2);
	solve(0, 0, 0, 0);
	for (int i = 0; i < (R2 - R1 + 1); i++)
		printf("%s\n", ans[i]);
}
