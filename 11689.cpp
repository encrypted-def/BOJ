#include <stdio.h>
int main(void) {
	long long n;
	scanf("%lld", &n);
	long long pi = n;
	long long prime = 2;
	while (prime * prime <= n) {
		if (n % prime == 0)
			pi = pi / prime * (prime - 1);
		while (n % prime == 0) // n에 prime 소인수를 전부 제거
			n = n / prime;
		prime++;
	}
	if (n != 1) { // 소인수가 남아있다면
		pi = pi / n * (n - 1);
	}
	printf("%lld", pi);
}
