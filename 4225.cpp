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
ll MOD = 1000000000;
ll POW(ll a, ll b, ll MMM = MOD) { ll ret = 1; for (; b; b >>= 1, a = (a*a) % MMM)if (b & 1)ret = (ret*a) % MMM; return ret; }
ll GCD(ll a, ll b) { return b ? GCD(b, a%b) : a; }
ll LCM(ll a, ll b) { if (a == 0 || b == 0)return a + b; return a * (b / GCD(a, b)); }
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
#define pb(x) push_back(x)
#define all(x) (x).begin(), (x).end()
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

double triArea(pll a, pll b, pll c) {
	return 0.5*abs((a.X*b.Y + b.X * c.Y + c.X * a.Y - b.X*a.Y - c.X*b.Y - a.X*c.Y));
}
double distV(pll v1, pll v2) {
	return sqrt((v1.X - v2.X)*(v1.X - v2.X) + (v1.Y - v2.Y) * (v1.Y - v2.Y));
}
double distVE(pll v, pll e1, pll e2) {
	if (v == e1)
		return 0.0;
	if (v == e2)
		return 0.0;
	if (e1 == e2)
		return distV(v, e1);
	double d1 = distV(v, e1);
	double d2 = distV(v, e2);
	double d3 = distV(e1, e2);
	//	if ((d1*d1 >= d2 * d2 + d3 * d3) || (d2*d2 >= d1 * d1 + d3 * d3)) // 둔각삼각형일 경우
	//		return min(d1, d2);
	return 2.0 * triArea(v, e1, e2) / d3;
}
bool point_cmp1(pll a, pll b) {
	if (a.Y == b.Y) return a.X < b.X;
	return a.Y < b.Y;
}
bool point_cmp2(pll a, pll b) {
	if (a.Y*b.X == a.X*b.Y) return point_cmp1(a, b);
	return a.Y*b.X < a.X*b.Y;
}
int CCW(pll a, pll b, pll c) {
	ll val = (b.X - a.X)*(c.Y - a.Y) - (b.Y - a.Y)*(c.X - a.X);
	if (val > 0) return 1;
	else if (val == 0) return 0;
	return -1;
}
vector < pll > GRAHAM(const vector< pll >& P) {
	vector< pll > Pcpy = P;
	sort(all(Pcpy), point_cmp1); // sort by y-axis
	ll mvX = Pcpy[0].X;
	ll mvY = Pcpy[0].Y;
	rep(i, 0, Pcpy.size()) {
		Pcpy[i].X -= mvX;
		Pcpy[i].Y -= mvY;
	}
	sort(Pcpy.begin() + 1, Pcpy.end(), point_cmp2); // sort by angle
	si S;
	S.push(0);
	S.push(1);
	int cur = 2;
	while (cur < Pcpy.size()) {
		while (S.size() >= 2) {
			int a1 = S.top(); S.pop();
			int a2 = S.top();
			if (CCW(Pcpy[a2], Pcpy[a1], Pcpy[cur]) >= 0) {
				S.push(a1);
				break;
			}
		}
		S.push(cur++);
	}
	vi idx;
	while (!S.empty()) {
		idx.pb(S.top());
		S.pop();
	}
	reverse(all(idx));
	vector< pll > ret;
	rep(i, 0, idx.size()) {
		ret.pb(make_pair(Pcpy[idx[i]].X + mvX, Pcpy[idx[i]].Y + mvY));
	}

	return ret;
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout << fixed;
	cout.precision(2);
	int T = 0;
	while (true) {
		int N;
		sf1(N);
		if (N == 0) return 0;
		T++;
		vector< pll > P(N);
		rep(i, 0, N) sf2(P[i].X, P[i].Y);
		vector< pll > graham = GRAHAM(P);
		double mn = 1e10;
		pll e1 = graham[0];
		pll e2 = graham[graham.size() - 1];
		double localmx = 0.0;
		rep(i, 0, graham.size()) {
			double dist = distVE(graham[i], e1, e2);
			if (localmx < dist) localmx = dist;
		}
		mn = localmx;
		rep(i, 0, graham.size() - 1) {
			double localmx = 0.0;
			pll e1 = graham[i];
			pll e2 = graham[i + 1];
			rep(j, 0, graham.size()) {
				double dist = distVE(graham[j], e1, e2);
				if (localmx < dist) localmx = dist;
			}
			if (mn > localmx) mn = localmx;
		}
		mn += 0.004999999999; // 0.01의 배수 조건 때문에
		cout << "Case" << ' ' << T << ": " << mn << '\n';
	}
}
