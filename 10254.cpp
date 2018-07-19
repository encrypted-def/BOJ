# pragma GCC optimize ("O3")
# pragma GCC optimize ("Ofast")
# pragma GCC optimize ("unroll-loops")

#include <bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>

#pragma warning(disable:4996)
#pragma comment(linker, "/STACK:336777216")

using namespace std;
//using namespace __gnu_pbds;

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
//typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>ordered_set;

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
class Rcali { // Convex Hull and Rotating Calipers
public:
	int pnum, chnum; // 모든 점의 갯수, ConvexHull을 이루는 점의 갯수
	vector<pll> p, ch; // 모든 점의 목록, ConvexHull을 이루는 점의 목록
	int CCW(pll a, pll b, pll c) {
		ll val = (b.X - a.X)*(c.Y - a.Y) - (b.Y - a.Y)*(c.X - a.X);
		if (val > 0) return 1;
		else if (val == 0) return 0;
		return -1;
	}
	void GScan() { // Graham Scan
		swap(p[0], *min_element(all(p))); // p[0]에 x가 가장 작은 원소를 담음
		sort(p.begin() + 1, p.end(), [this](pll a, pll b) {
			int ccw = CCW(p[0], a, b);
			return ccw > 0 || (ccw == 0 && a < b); // 뒷 부분은 일직선 상에 있을 때 order를 정해주는 것
		});
		rep(i, 0, pnum) {
			while (chnum > 1 && CCW(ch[chnum - 2], ch[chnum - 1], p[i]) <= 0) chnum--;
			ch[chnum++] = p[i];
		}
		ch.resize(chnum);
	}
	pair<pll, pll > diameter() { // 가장 먼 두 점을 반환
		GScan();
		ll mx = 0;
		pair<pll, pll > ans;
		for (int i = 0, j = 1; i < chnum; i++) {
			int inxt = (i + 1) % chnum;
			int jnxt = (j + 1) % chnum;
			while (CCW(ch[i], ch[inxt], { ch[i].X + ch[jnxt].X - ch[j].X, ch[i].Y + ch[jnxt].Y - ch[j].Y }) == 1) {
				j = jnxt;
				jnxt = (j + 1) % chnum;
			}
			ll dist = (ch[i].X - ch[j].X) * (ch[i].X - ch[j].X) + (ch[i].Y - ch[j].Y) * (ch[i].Y - ch[j].Y);
			if (mx < dist) {
				mx = dist;
				ans.X = ch[i];
				ans.Y = ch[j];
			}
		}
		return ans;
	}
	Rcali(int _pnum) {
		pnum = _pnum;
		chnum = 0;
		p.resize(pnum);
		ch.resize(pnum);
	}
};

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int T;
	sf1(T);
	while (T--) {
		int N;
		sf1(N);
		Rcali RC(N);
		rep(i, 0, N) sf2(RC.p[i].X, RC.p[i].Y);
		pair<pll, pll> ans = RC.diameter();
		pf4l(ans.X.X, ans.X.Y, ans.Y.X, ans.Y.Y);
	}
}
