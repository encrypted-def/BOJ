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
const int dx[4] = { 1,-1,0,0 };
const int dy[4] = { 0,0,1,-1 };
const int ddx[8] = { 0,0,1,1,1,-1,-1,-1 }, ddy[8] = { 1,-1,1,0,-1,1,0,-1 };
const int INF = 0x7f7f7f7f;
const ll INF_LL = 0x7f7f7f7f7f7f7f7f;
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

int main(void) {
	int T;
	sf1(T);
	while (T--) {
		int N, K;
		sf2(N, K);
		int R[10003][5];
		rep(i, 0, N)
			rep(j, 0, 5)
				sf1(R[i][j]);
		int mx[32]; // mx[10010] -> 1, 4번 능력의 합의 최댓값
		fill(mx, mx + 32, -INF);
		rep(bitmask, 1, 32) {
			rep(i, 0, N) {
				int tmp = 0;
				rep(j, 0, 5) {
					if (bitmask & (1 << j)) {
						tmp += R[i][j];
					}
				}
				if (mx[bitmask] < tmp) mx[bitmask] = tmp;
			}
		}
		if (K == 1) {
			pf1l(mx[31]);
			continue;
		}
		if (K >= 5) {
			pf1l(mx[1] + mx[2] + mx[4] + mx[8] + mx[16]);
			continue;
		}
		if (K == 2) {
			int ans = -INF;
			rep(a1, 1, 32) {
				if (mx[a1] + mx[31 - a1] > ans)
					ans = mx[a1] + mx[31 - a1];
			}
			pf1l(ans);
			continue;
		}
		if (K == 3) {
			int ans = -INF;
			rep(a1, 1, 32) {
				rep(a2, 1, 32 - a1) { // a1, a2, 31-a1-a2
					if (a1 & a2) continue; // a1 & a2는 0이어야 한다
					if (a1 & (31 - a1 - a2)) continue;
					if (a2 & (31 - a1 - a2)) continue;
					if (mx[a1] + mx[a2] + mx[31 - a1 - a2] > ans)
						ans = mx[a1] + mx[a2] + mx[31 - a1 - a2];
				}
			}
			pf1l(ans);
			continue;
		}
		int ans = -INF;
		rep(a1, 1, 32) {
			rep(a2, 1, a1) {
				if ((a1-a2) & a2) continue; // a1-a2, a2, a3, 31-a1-a3
				rep(a3, 1, 32 - a1) {
					if ((a1 - a2) & a3) continue;
					if ((a1 - a2) & (31 - a1 - a3)) continue;
					if (a2 & a3) continue;
					if (a2 & (31 - a1 - a3)) continue;
					if (a3 & (31 - a1 - a3)) continue;
					if (mx[a1 - a2] + mx[a2] + mx[a3] + mx[31 - a1 - a3] > ans)
						ans = mx[a1 - a2] + mx[a2] + mx[a3] + mx[31 - a1 - a3];
				}
			}
		}
		pf1l(ans);
	}
}
