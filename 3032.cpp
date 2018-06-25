# pragma GCC optimize ("O3")
# pragma GCC optimize ("Ofast")
# pragma GCC optimize ("unroll-loops")

#include <bits/stdc++.h>

#pragma warning(disable:4996)
#pragma comment(linker, "/STACK:336777216")
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef tuple<int, int, int> ti3;
typedef tuple<int, int, int, int> ti4;
typedef stack<int> si;
typedef queue<int> qi;
typedef priority_queue<int> pqi;
typedef pair<ll, ll> pll;
typedef vector<ll> vl;
typedef tuple<ll, ll, ll> tl3;
typedef tuple<ll, ll, ll, ll> tl4;
typedef stack<ll> sl;
typedef queue<ll> ql;
typedef priority_queue<ll> pql;
int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };
int ddx[8] = { 0,0,1,1,1,-1,-1,-1 }, ddy[8] = { 1,-1,1,0,-1,1,0,-1 };
ll POW(ll a, ll b, ll MMM) { ll ret = 1; for (; b; b >>= 1, a = (a*a) % MMM)if (b & 1)ret = (ret*a) % MMM; return ret; }
ll GCD(ll a, ll b) { return b ? GCD(b, a%b) : a; }
ll LCM(ll a, ll b) { if (a == 0 || b == 0)return a + b; return a / GCD(a, b) * b; }
ll INV(ll a, ll m) {
	ll m0 = m, y = 0, x = 1;
	if (m == 1)	return 0;
	while (a > 1) {
		ll q = a / m;
		ll t = m;
		m = a % m, a = t;
		t = y;
		y = x - q * y;
		x = t;
	}
	if (x < 0) x += m0;
	return x;
}
pll EXGCD(ll a, ll b) {
	if (b == 0) return { 1,0 };
	auto t = EXGCD(b, a%b);
	return { t.second,t.first - t.second*(a / b) };
}
bool OOB(ll x, ll y, ll N, ll M) { return 0 > x || x >= N || 0 > y || y >= M; }
#define X first
#define Y second
#define rep(i,a,b) for(int i = a; i < b; i++)
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(a) ((int)(a.size()))
#define sf1(a) cin >> a
#define sf2(a,b) cin >> a >> b
#define sf3(a,b,c) cin >> a >> b >> c
#define sf4(a,b,c,d) cin >> a >> b >> c >> d
#define sf5(a,b,c,d,e) cin >> a >> b >> c >> d >> e
#define sf6(a,b,c,d,e,f) cin >> a >> b >> c >> d >> e >> f
#define pf1(a) cout << (a) << ' '
#define pf2(a,b) cout << (a) << ' ' << (b) << ' '
#define pf3(a,b,c) cout << (a) << ' ' << (b) << ' '<< (c) << ' '
#define pf4(a,b,c,d) cout << (a) << ' ' << (b) << ' '<< (c) << ' '<< (d) << ' '
#define pf5(a,b,c,d,e) cout << (a) << ' ' << (b) << ' '<< (c) << ' '<< (d) << ' '<< (e) << ' '
#define pf6(a,b,c,d,e,f) cout << (a) << ' ' << (b) << ' '<< (c) << ' '<< (d) << ' '<< (e) << ' ' << (f) << ' '
#define pf0l() cout << '\n';
#define pf1l(a) cout << (a) << '\n'
#define pf2l(a,b) cout << (a) << ' ' << (b) << '\n'
#define pf3l(a,b,c) cout << (a) << ' ' << (b) << ' '<< (c) << '\n'
#define pf4l(a,b,c,d) cout << (a) << ' ' << (b) << ' '<< (c) << ' '<< (d) << '\n'
#define pf5l(a,b,c,d,e) cout << (a) << ' ' << (b) << ' '<< (c) << ' '<< (d) << ' '<< (e) << '\n'
#define pf6l(a,b,c,d,e,f) cout << (a) << ' ' << (b) << ' '<< (c) << ' '<< (d) << ' '<< (e) << ' ' << (f) << '\n'
#define pfvec(V) for(auto const &t : V) pf1(t)
#define pfvecl(V) for(auto const &t : V) pf1(t); pf0l()
ll D[204][204];
int over[204][204];
int isZero[204][204];
const ll MOD = 1e5;
ll kind(char a, char b) {
	if (a == '?') {
		if (b == '?')
			return 3;
		else if (b == ')' || b == ']' || b == '}')
			return 1;
		else
			return 0;
	}
	if (b == '?') {
		if (a == '(' || a == '[' || a == '{')
			return 1;
		else
			return 0;
	}
	if (a == '(' && b == ')')
		return 1;
	else if (a == '[' && b == ']')
		return 1;
	else if (a == '{' && b == '}')
		return 1;
	return 0;
}
int main(void) {
	//ios::sync_with_stdio(false);
	//cin.tie(0);
	int N;
	string S;
	sf2(N, S);
	rep(i, 0, 201) {
		rep(j, 0, 201) {
			isZero[i][j] = 1;
		}
	}
	if (N % 2 != 0) {
		pf1l(0);
		return 0;
	}
	rep(i, 0, N + 1) {
		D[i][i] = 1;
		isZero[i][i] = 0;
	}
	rep(i, 0, N - 1) {
		D[i][i + 2] = kind(S[i], S[i + 1]);
		isZero[i][i + 2] = (D[i][i + 2] == 0);
	}
	for (int gap = 4; gap <= N; gap++) {
		for (int i = 0; i <= N - gap; i++) {
			for (int sep = i + 1; sep < i + gap; sep += 2) {
				D[i][i + gap] += kind(S[i], S[sep])*D[i + 1][sep] * D[sep + 1][i + gap];
				if (kind(S[i], S[sep]) != 0 && !isZero[i + 1][sep] && !isZero[sep + 1][i + gap])
					isZero[i][i + gap] = 0;
				if (D[i][i + gap] >= MOD) {
					D[i][i + gap] %= MOD;
					over[i][i + gap] = 1;
				}
				if (kind(S[i], S[sep]) != 0 && (over[i + 1][sep] || over[sep + 1][i + gap]))
					over[i][i + gap] = 1;
			}
		}
	}
	if (!isZero[0][N] && over[0][N])
		printf("%05d\n", D[0][N]);
	else
		printf("%d\n",D[0][N]);
}
