#include <stdio.h>
#include <math.h>
typedef long long ll;
ll N, K;
double harmoni1(ll n) { // for문으로 H(n) 계산
	long double Hn = 0.0;
	for (ll i = 1; i <= n; i++)
		Hn += 1.0 * N / i;
	return Hn;
}
double harmoni2(ll n) { // 근사식으로 H(n) 계산
	long double Gamma = 0.57721566490153286060651209008240243104215933593992; // Euler–Mascheroni_constant
	return N * log1p(n - 1) + N * Gamma + N * 0.5 / n - N * 1.0 / 12 / n / n + N * 1.0 / 120 / n / n / n / n;
}
double brute_smallK() {
	long double ans = 0.0;
	for (ll i = N - K + 1; i <= N; i++)
		ans += 1.0 * N / i;
	return ans;
}
double harmoni(ll n) {
	if (n > 1000000)
		return harmoni2(n);
	else
		return harmoni1(n);
}
int sign(int n) {
	if (n % 2 == 0)
		return -1;
	return 1;
}
double ln_taylor2() {
	// x = K / (N-K);
	int approx = 100000;
	double ans = 0;
	double pow = 1.0 * N / (N - K) * K;
	for (int i = 1; i <= approx; i++) {
		ans += pow / i * sign(i);
		pow = pow * K / (N-K);
		if (pow == 0.0)
			break;
	}
	return ans;
}
int main(void) {
	scanf("%lld %lld", &N, &K);
	
	if (K < 20000000LL) {
		printf("%.10f\n", brute_smallK());
		return 0;
	}
	if (K < 10000000000000LL && K < N/10) {
		ll A = N - K;
		printf("%.10f\n", ln_taylor2() + 0.5 - 0.5*N / A + 1.0 / 12 / N - 1.0*N / 12 / A / A);
		return 0;
	}
	printf("%.10f", harmoni(N) - harmoni(N - K));
	return 0;
}
