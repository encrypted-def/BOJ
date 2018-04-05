#include <stdio.h>
int N, M;
int t[10004];
long long capacity(long long T) {
	long long val = 0;
	for (int i = 0; i < M; i++)
		val += T / t[i] + 1;
	return val;
}
int main(void) {
	scanf("%d %d", &N, &M);
	for (int i = 0; i < M; i++)
		scanf("%d", &t[i]);
	if (N <= M) {
		printf("%d", N);
		return 0;
	}
	long long st = 0;
	long long en = N * 30L + 10;
	while (en - st > 40) {
		long long mid = (st + en) / 2;
		if (capacity(mid) >= N)
			en = mid;
		else 
			st = mid;
	}
	long long cur = capacity(st);
	st++;
	while (true) {
		for (int i = 0; i < M; i++) {
			if (st % t[i] == 0) {
				cur++;
				if (cur == N) {
					printf("%d", i + 1);
					return 0;
				}
			}
		}
		st++;
	}
}
