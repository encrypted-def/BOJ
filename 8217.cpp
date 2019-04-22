# pragma GCC optimize ("O3")
# pragma GCC optimize ("Ofast")
# pragma GCC optimize ("unroll-loops")
# pragma GCC target("sse,sse2,sse3,ssse3,sse4,avx,avx2")
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

int n,m,q;
int o[300005];
int p[300005];
vi region[300005];
ti3 meteor[300005];
int st[300005],en[300005],mid[300005];
class Seg { // 0-indexed
public:
  int n;
  vector<ll> a;
  Seg(int n) : n(n), a(2*n) {}
  void init() {
    for (int i = n - 1; i > 0; i--) a[i] = a[i << 1] + a[i << 1|1];
  }
  void update(int i, ll val) { // add i-th element to val(0-indexed)
    for (a[i += n] += val; i > 1; i >>= 1) a[i >> 1] = a[i] + a[i ^ 1];
  }
  // sum of l-th to r-th element(0-indexed)
  ll query(int l, int r) {
    ll ret = 0;
    for (l += n, r += n+1; l < r; l >>= 1, r >>= 1) {
      if (l & 1) ret += a[l++];
      if (r & 1) ret += a[--r];
    }
    return ret;
  }
  void pushval(int i, ll val){ // set i-th element to val
    a[i+n]=val;
  }
};

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout << fixed;
  cout.precision(20);
///////////////////////////////////////////////
  sf2(n,m);
  rep(i,1,m+1){
    sf1(o[i]);
    region[o[i]].pb(i);
  }
  rep(i,1,n+1){
    sf1(p[i]);
  }
  sf1(q);
  rep(i,1,q+1){
    int l,r,a;
    sf3(l,r,a);
    meteor[i] = {l,r,a};
  }
  fill(st+1,st+n+1,0);
  fill(en+1,en+n+1,q+1);
  fill(mid+1,mid+n+1,(q+1)/2);
  while(1){
    bool upd = 0; // st to en range가 바뀐게 있는가?
    pii query[n];
    rep(i,0,n) query[i] = {mid[i+1], i+1};
    sort(query,query+n);
    Seg SS(m+2);
    int midx = 1; // midx번째 meteor부터 떨구면 됨
    rep(i,0,n){
      if(st[query[i].Y] == en[query[i].Y] or st[query[i].Y] == q+1) continue; // 이미 결과가 특정된 경우
      upd = 1;
      while(midx <= query[i].X){
        int l,r,a;
        tie(l,r,a) = meteor[midx];
        if(l <= r){
          SS.update(l,a);
          SS.update(r+1,-a);
        }
        else{
          SS.update(l,a);
          SS.update(1,a);
          SS.update(r+1,-a);
        }
        midx++;
      }
      ll tot = 0; // 수집된 샘플의 수
      for(auto e : region[query[i].Y]){
        tot += SS.query(1,e);
        if(tot >= p[query[i].Y]) break;
      }
      if(tot >= p[query[i].Y])
        en[query[i].Y] = query[i].X;
      else
        st[query[i].Y] = query[i].X+1;
      mid[query[i].Y] = (st[query[i].Y]+en[query[i].Y])/2;
    }
    if(!upd) break;
  }
  rep(i,1,n+1){
    if(mid[i] == q+1) pf1l("NIE");
    else pf1l(mid[i]);
  }
}
