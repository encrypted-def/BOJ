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
int N;
pii point[5001][2];
int p[5001]; // must initialized with -1
int UF_find(int x) {
	if (p[x] < 0) return x;
	return p[x] = UF_find(p[x]);
}
bool UF_union(int a, int b) {
	a = UF_find(a);
	b = UF_find(b);
	if (a == b) return false;
	if (p[b] < p[a]) // b가 더 많이 가지고 있으면
		swap(a, b);
	p[a] += p[b];
	p[b] = a;
	return true;
}
int CCW(pll a, pll b, pll c) {
	ll val = (b.X - a.X)*(c.Y - a.Y) - (b.Y - a.Y)*(c.X - a.X);
	if (val > 0) return 1;
	else if (val == 0) return 0;
	return -1;
}
bool intersectLine(pll e11, pll e12, pll e21, pll e22) {
	if (CCW(e11, e12, e21) == 0) {
		if (min(e11.X, e12.X) <= e21.X && e21.X <= max(e11.X, e12.X) && min(e11.Y, e12.Y) <= e21.Y && e21.Y <= max(e11.Y, e12.Y))
			return true;
	}
	if (CCW(e11, e12, e22) == 0) {
		if (min(e11.X, e12.X) <= e22.X && e22.X <= max(e11.X, e12.X) && min(e11.Y, e12.Y) <= e22.Y && e22.Y <= max(e11.Y, e12.Y))
			return true;
	}
	if (CCW(e21, e22, e11) == 0) {
		if (min(e21.X, e22.X) <= e11.X && e11.X <= max(e21.X, e22.X) && min(e21.Y, e22.Y) <= e11.Y && e11.Y <= max(e21.Y, e22.Y))
			return true;
	}
	if (CCW(e21, e22, e12) == 0) {
		if (min(e21.X, e22.X) <= e12.X && e12.X <= max(e21.X, e22.X) && min(e21.Y, e22.Y) <= e12.Y && e12.Y <= max(e21.Y, e22.Y))
			return true;
	}
	if (CCW(e11, e12, e21) == 0 && CCW(e11, e12, e22) == 0) return false;
	return CCW(e11, e12, e21)*CCW(e11, e12, e22) <= 0 && CCW(e21, e22, e12)*CCW(e21, e22, e11) <= 0;
}
int main(void) {
	sf1(N);
	rep(i, 0, N) {
		sf4(point[i][0].X, point[i][0].Y, point[i][1].X, point[i][1].Y);
		p[i] = -1;
	}
	rep(i, 1, N) {
		rep(j, 0, i) {
			if (intersectLine(point[i][0], point[i][1], point[j][0], point[j][1]))
				UF_union(i, j);
		}
	}
	int cnt1 = 0, cnt2 = 0;
	rep(i, 0, N) {
		if (p[i] < 0)cnt1++;
		cnt2 = max(cnt2, -p[i]);
	}
	pf1l(cnt1);
	pf1l(cnt2);
}
