#include <stdio.h>
#include <algorithm>
using namespace std;
typedef pair<pair<long long, long long>, pair<long long, long long> > MATRIX;
#define X first
#define Y second
const long long MOD = 1000000007LL;

MATRIX mul(MATRIX a, MATRIX b) {
	return { {(a.X.X*b.X.X + a.X.Y*b.Y.X) % MOD,(a.X.X*b.X.Y + a.X.Y*b.Y.Y) % MOD},{ (a.Y.X*b.X.X + a.Y.Y*b.Y.X) % MOD,(a.Y.X*b.X.Y + a.Y.Y*b.Y.Y) % MOD} };
}
MATRIX pow(long long a) {
	if (a == 0)
		return { {1LL,0LL},{0LL,1LL} };
	if (a == 1)
		return { {1LL, 1LL}, {1LL, 0LL} };
	MATRIX tmp = pow(a / 2);
	if (a % 2 == 0)
		return mul(tmp, tmp);
	else
		return mul(mul(tmp, tmp), { {1LL,1LL},{1LL,0LL} });
}

long long fibo(long long a) {
	return pow(a).X.Y;
}
long long gcd(long long n, long long m) {
	if (n == 0LL)
		return m;
	return gcd(m%n, n);
}
int main(void) {
	long long n, m;
	scanf("%lld %lld", &n, &m);
	long long g = gcd(n, m);
	printf("%lld", fibo(g));
}
