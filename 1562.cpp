#include <stdio.h>
int D[105][10][1024]; // D[i][j][k] : i자리, 끝자리가 j, 사용된 숫자의 상태가 k
const int MOD = 1000000000;
bool stateIn(int state, int digit) {
	return state & (1 << (9 - digit));
}
int bit_digit(int digit) {
	return 1 << (9 - digit);
}
int main(void) {

	for(int i = 1; i <= 9; i++)
		D[1][i][1<<(9-i)] = 1;
	int N;
	scanf("%d", &N);
	for (int i = 2; i <= N; i++) {
		for (int j = 0; j <= 9; j++) {
			for (int k = 1; k < 1024; k++) {
				if (!stateIn(k,j))
					continue;
				if (j != 0) {
					D[i][j][k] = (D[i][j][k] + D[i-1][j - 1][k]) % MOD;
					D[i][j][k] = (D[i][j][k] + D[i-1][j - 1][k ^ bit_digit(j)]) % MOD;
				}
				if (j != 9) {
					D[i][j][k] = (D[i][j][k] + D[i-1][j + 1][k]) % MOD;
					D[i][j][k] = (D[i][j][k] + D[i-1][j + 1][k ^ bit_digit(j)]) % MOD;
				}
			}
		}
	}
	int result = 0;
	for (int j = 0; j <= 9; j++)
		result = (result + D[N][j][1023]) % MOD;
	printf("%d", result);
}
