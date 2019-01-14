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
class SegLazy { // 1-indexed
public:
  vector<int> seg, lazy;
  int n;
  SegLazy(int n):n(n) {
    seg.resize(4 * n + 4);
    lazy.resize(4 * n +4);
  }
  void updateLazy(int node, int nl, int nr) {
    seg[node] = lazy[node];
    if (nl != nr) {
      lazy[2 * node] = lazy[node];
      lazy[2 * node + 1] = lazy[node];
    }
    lazy[node] = 0;
  }
  // add val to i-th element ~ j-th element
  void update(int i, int j, int val, int node, int nl, int nr) {
    if (lazy[node] != 0)
      updateLazy(node, nl, nr);
    if (j<nl or i>nr) return;
    if (i <= nl and nr <= j) {
      lazy[node] = val;
      updateLazy(node, nl, nr);
      return;
    }
    int mid = (nl + nr) / 2;
    update(i, j, val, 2 * node, nl, mid);
    update(i, j, val, 2 * node + 1, mid + 1, nr);
    seg[node] = seg[2 * node] | seg[2 * node + 1];
  }
  void update(int i, int j, int val){ // 1-indexed
    update(i,j,val,1,1,n);
  }
  // sum of i-th to j-th element
  int query(int i, int j, int node, int nl, int nr) {
    if (lazy[node] != 0) updateLazy(node, nl, nr);
    if (j<nl || i>nr) return 0;
    if (i <= nl && nr <= j) return seg[node];
    int mid = (nl + nr) / 2;
    return query(i, j, 2 * node, nl, mid)|query(i, j, 2 * node + 1, mid + 1, nr);
  }
  int query(int i, int j){ // 1-indexed
    return query(i,j,1,1,n);
  }
};
int n,t,q;
int main(void) {
	//ios::sync_with_stdio(false);
	cin.tie(0);
  sf3(n,t,q);
  SegLazy SS(n+4);
  SS.update(1,n,1);
  while(q--){
    string a;
    cin >> a;
    if(a=="C"){
      int x,y,z;
      sf3(x,y,z);
      if(x>y) swap(x,y);
      SS.update(x,y,1<<(z-1));
    }
    else{
      int x,y;
      sf2(x,y);
      if(x>y) swap(x,y);
      int val = SS.query(x,y);
      pf1l(__builtin_popcount(val));
    }
  }
}
