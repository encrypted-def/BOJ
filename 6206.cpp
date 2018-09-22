# pragma GCC optimize ("O3")
# pragma GCC optimize ("Ofast")
# pragma GCC optimize ("unroll-loops")

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/rope>

using namespace std;
using namespace __gnu_pbds;
using namespace __gnu_cxx;

typedef unsigned int ui;
typedef long long ll;
typedef unsigned long long ull;
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
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>ordered_set;

const int dx[4] = { 1,0,-1,0 };
const int dy[4] = { 0,1,0,-1 };
const int ddx[8] = { 0,0,1,1,1,-1,-1,-1 }, ddy[8] = { 1,-1,1,0,-1,1,0,-1 };
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

////////////////////////////////////////////////
////1. http://blog.myungwoo.kr/57 //////////////
////2. S,sa : 1-indexed, lcp : 2-indexed////////
//banana -> sa=(6 4 2 1 5 3), lcp=(1 3 0 0 2)///
////////////////////////////////////////////////
class SA {
public:
	int N;
	int num; // 등장 가능한 문자의 갯수
	vector<int> sa,lcp;
	vector<int> S;
	SA(int _N, int _num) {
		N = _N;
		sa.resize(N + 1), lcp.resize(N + 1);
		num = _num;
	}
	void FindSA() {
		int i, j, k;
		int m = num;
		vector <int> cnt(max(N, m) + 1, 0), x(N + 1, 0), y(N + 1, 0);
		rep(i,1,N+1) cnt[x[i] = S[i] + 1]++;
		rep(i,1,m+1) cnt[i] += cnt[i - 1];
		for (i = N; i; i--) sa[cnt[x[i]]--] = i;
		for (int len = 1, p = 1; p < N; len <<= 1, m = p) {
			for (p = 0, i = N - len; ++i <= N;) y[++p] = i;
			rep(i, 1, N + 1) if (sa[i] > len) y[++p] = sa[i] - len;
			rep(i, 0, m + 1) cnt[i] = 0;
			rep(i, 1, N + 1) cnt[x[y[i]]]++;
			rep(i, 1, m + 1) cnt[i] += cnt[i - 1];
			for (i = N; i; i--) sa[cnt[x[y[i]]]--] = y[i];
			swap(x, y); p = 1; x[sa[1]] = 1;
			rep(i, 1, N)
				x[sa[i + 1]] = sa[i] + len <= N && sa[i + 1] + len <= N && y[sa[i]] == y[sa[i + 1]] && y[sa[i] + len] == y[sa[i + 1] + len] ? p : ++p;
		}
	}
	void FindLCP() {
		int i, j, k = 0;
		vector<int> rnk(N + 1, 0);
		rep(i,1,N+1) rnk[sa[i]] = i;
		for (i = 1; i <= N; lcp[rnk[i++]] = k)
			for (k ? k-- : 0, j = sa[rnk[i] - 1]; S[i + k] == S[j + k]; k++);
	}
};

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0);
  int N,K;
  sf2(N,K);
  SA sa(N,1000001);
  sa.S.resize(N+1,-1);
  rep(i,1,N+1) sf1(sa.S[i]);
  sa.FindSA();
  sa.FindLCP();
  multiset<int> S;
  int mx = 0;
  rep(i,2,N+1){
    pf1l(sa.lcp[i]);
  }
  rep(i,2,2+K-1) S.insert(sa.lcp[i]);
  mx = max(mx,*S.begin());
  rep(i,2+K-1,N+1){
    S.erase(S.find(sa.lcp[i-(K-1)]));
    S.insert(sa.lcp[i]);
    mx = max(mx,*S.begin());
  }
  pf1l(mx);
}
