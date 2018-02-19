#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
int D[1 << 15][17]; // D[i][j] -> i : bitmask j : 마지막으로 그림을 소유한 사람
int N;
char price[17][17];
int vec2i(vector<int> V) {
	int a = 0;
	for (auto val : V) {
		a = ((a << 1) | val);
	}
	return a;
}
int bit(int i) {
	return 1 << (N-1-i);
}
int main(void) {
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%s", price[i]);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			price[i][j] -= '0';
	for (int i = 0; i < (1 << N); i++)
		for (int j = 0; j < N; j++)
			D[i][j] = 0x7ffff;
	D[bit(0)][0] = 0;
	int ans = 1;
	for (int buyer = 2; buyer <= N; buyer++) {
		vector<int> tmp(N);
		for (int i = N - buyer; i < N; i++)
			tmp[i] = 1;
		do { // 소유자가 buyer명인 모든 조합에 대해
			int bitmask1 = vec2i(tmp);
			for (int i = 0; i < N; i++) {
				if (tmp[i] == 1) {
					// i번째 예술가가 마지막으로 획득하는 상황으로 만듬
					int bitmask2 = bitmask1 - bit(i);
					for (int lst = 0; lst < N; lst++) { // lst : 두번째 마지막으로 그림을 산 사람. lst가 i에게 그림을 팔 것임
						if (lst == i)
							continue;
						if (D[bitmask2][lst] <= price[lst][i] && price[lst][i] < D[bitmask1][i]) {
							D[bitmask1][i] = price[lst][i];
							ans = buyer;
						}
					}
				}
			}
		} while (next_permutation(tmp.begin(), tmp.end()));
	}
	printf("%d", ans);
}
