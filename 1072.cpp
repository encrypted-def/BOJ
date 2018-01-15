#include <stdio.h>
typedef long long ll;
int main(void) {
	ll X, Y, Z;
	while (scanf("%lld %lld", &X, &Y) != EOF) {
		Z = 100 * Y / X;
		if (Z >= 99)
			printf("-1\n");
		else {
			ll a = X*Z + X - 100 * Y;
			ll b = 99 - Z;
			ll k = a / b;
			if (k * b < a)
				k++;
			printf("%lld\n", k);
		}
	}
	return 0;
}
