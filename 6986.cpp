#include <stdio.h>
#include <algorithm>
using namespace std;
int N, K;
long long a[100004];
int main(void) {
	scanf("%d %d", &N, &K);
	for (int i = 0; i < N; i++) {
		char s[10];
		scanf("%s", &s);
		if (s[3] == 0)
			a[i] = (s[0] - '0') * 1000 + (s[2] - '0')*100;
		else
			a[i] = 10000;
	}
	sort(a, a + N);
	long long sum1 = 0;
	long long sum2 = 0;
	sum2 += a[K]*K + a[N-K-1]*K;
	for (int i = K; i < N - K; i++) {
		sum1 += a[i];
		sum2 += a[i];
	}
	long long avg1 = sum1 / (N - 2 * K);
	long long avg2 = sum2 / N;
	avg1 += 5;
	avg2 += 5;
	avg1 /= 10;
	avg2 /= 10;
	printf("%lld.%02lld\n%lld.%02lld", avg1 / 100, avg1 % 100, avg2 / 100, avg2 % 100);
}
