#include <stdio.h>
#include <string.h>
bool istidy(long long N) {
	int a = 10;
	while (N > 0) {
		if (a < N % 10)
			return false;
		a = N % 10;
		N = N / 10;
	}
	return true;
}
int len(long long N) {
	int cnt = 0;
	while (N > 0) {
		cnt++;
		N /= 10;
	}
	return cnt;
}
long long pow10(int e) {
	long long val = 1;
	while (e--) val *= 10;
	return val;
}
int main(void) {
	int T;
	scanf("%d", &T);
	for (int Case = 1; Case <= T; Case++) {
		printf("Case #%d: ", Case);
		long long N;
		scanf("%lld", &N);
		if (istidy(N)) {
			printf("%lld\n", N);
			continue;
		}
		int digitN = len(N);
		long long tmp = N;
		int cnt = 0;
		while (tmp > 0) {
			tmp /= 10;
			cnt++;
			if (tmp % 10 == 0)
				continue;
			long long val = tmp*pow10(cnt) - 1;
			if (istidy(val)) {
				printf("%lld\n", val);
				break;
			}
		}
	}
}
