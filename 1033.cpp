#include <stdio.h>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> PAIR; // {2, 3} : 2/3을 의미
#define X first
#define Y second
int N;
PAIR material[11];
PAIR ratio[11][11]; // ratio[a][b] : a가 1일 때 b가 얼마인지.
ll gcd(ll a, ll b) {
	if (a == 0ll)
		return b;
	return gcd(b%a, a);
}
ll lcm(ll a, ll b) {
	return a / gcd(a, b) * b;
}
PAIR mul(PAIR a, PAIR b) {
	ll c = a.X * b.X;
	ll d = a.Y * b.Y;
	ll g = gcd(c, d);
	return { c / g, d / g };
}
int main(void) {
	scanf("%d", &N);
	if (N == 1) {
		printf("1");
		return 0;
	}
	for (int i = 0; i < N - 1; i++) {
 		int a, b, p, q;
		scanf("%d %d %d %d", &a, &b, &p, &q);
		ratio[a][b] = { q,p };
		ratio[b][a] = { p,q };
	}
	material[0] = { 1,1 };
	for (int repeat = 0; repeat < N; repeat++) {
		for (int i = 0; i < N; i++) {
			if (material[i].X == 0)
				continue;
			for (int j = 0; j < N; j++) { // i로부터 j를 갱신할 예정
				if (ratio[i][j].X == 0 || material[j].X != 0)
					continue;
				material[j] = mul(material[i], ratio[i][j]);
			}
		}
	}
	ll l = lcm(material[0].Y, material[1].Y);
	for (int i = 2; i < N; i++)
		l = lcm(l, material[i].Y);
	for (int i = 0; i < N; i++)
		printf("%lld ", material[i].X * l / material[i].Y);
}
