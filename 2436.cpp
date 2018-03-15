#include <stdio.h>
int gcd(int a, int b) {
	if (a == 0)
		return b;
	return gcd(b%a, a);
}
int main(void) {
	int g, l;
	scanf("%d %d", &g, &l);
	int val = 1;
	int f = l / g;
	for (int i = 2; i*i <= f; i++) {
		if (f%i == 0 && gcd(i, f / i) == 1)
			val = i;
	}
	printf("%d %d", g*val, g*(f / val));
}
