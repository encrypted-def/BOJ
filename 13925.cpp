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

ll mod = 1e9+7;
class SegLazy { // 1-indexed
public:
  vector<ll> seg, lazy1, lazy2;
  int n;
  SegLazy(int n):n(n),seg(4*n+4),lazy1(4*n+4,1),lazy2(4*n+4){}
  void updateLazy(int node, int nl, int nr) {
    seg[node] = (lazy1[node]*seg[node]+lazy2[node]*(nr-nl+1))%mod;  // change this
    if (nl != nr) {
      lazy1[2 * node] = (lazy1[2*node]*lazy1[node])%mod;
      lazy1[2 * node+1] = (lazy1[2*node+1]*lazy1[node])%mod;
      lazy2[2*node] = lazy1[node]*lazy2[2*node]%mod;
      lazy2[2*node+1] = lazy1[node]*lazy2[2*node+1]%mod;      
      lazy2[2 * node] = (lazy2[2*node]+lazy2[node])%mod;
      lazy2[2 * node+1] = (lazy2[2*node+1]+lazy2[node])%mod;
    }
    lazy1[node] = 1;
    lazy2[node] = 0;
  }
  // add val to i-th element ~ j-th element
  void upd1(int i, int j, ll val, int node, int nl, int nr) {
    if (lazy1[node] != 1 or lazy2[node] != 0)
      updateLazy(node, nl, nr);
    if (j<nl or i>nr) return;
    if (i <= nl and nr <= j) {
      lazy2[node] = val;
      updateLazy(node, nl, nr);
      return;
    }
    int mid = (nl + nr) / 2;
    upd1(i, j, val, 2 * node, nl, mid);
    upd1(i, j, val, 2 * node + 1, mid + 1, nr);
    seg[node] = (seg[2 * node] + seg[2 * node + 1])%mod; // change this
  }
  void upd1(int i, int j, ll val){ // 1-indexed
    upd1(i,j,val,1,1,n);
  }
  // multiply val to i-th element ~ j-th element
  void upd2(int i, int j, ll val, int node, int nl, int nr) {
    if (lazy1[node] != 1 or lazy2[node] != 0)
      updateLazy(node, nl, nr);
    if (j<nl or i>nr) return;
    if (i <= nl and nr <= j) {
      lazy1[node] = val;
      updateLazy(node, nl, nr);
      return;
    }
    int mid = (nl + nr) / 2;
    upd2(i, j, val, 2 * node, nl, mid);
    upd2(i, j, val, 2 * node + 1, mid + 1, nr);
    seg[node] = (seg[2 * node]+ seg[2 * node + 1])%mod; // change this
  }
  void upd2(int i, int j, ll val){ // 1-indexed
    upd2(i,j,val,1,1,n);
  }

  // change i-th element ~ j-th element = val
  void upd3(int i, int j, ll val, int node, int nl, int nr) {
    if (lazy1[node] != 1 or lazy2[node] != 0)
      updateLazy(node, nl, nr);
    if (j<nl or i>nr) return;
    if (i <= nl and nr <= j) {
      lazy1[node] = 0;
      lazy2[node] = val;
      updateLazy(node, nl, nr);
      return;
    }
    int mid = (nl + nr) / 2;
    upd3(i, j, val, 2 * node, nl, mid);
    upd3(i, j, val, 2 * node + 1, mid + 1, nr);
    seg[node] = (seg[2 * node]+ seg[2 * node + 1])%mod; // change this
  }
  void upd3(int i, int j, ll val){ // 1-indexed
    upd3(i,j,val,1,1,n);
  }
  
  // sum of i-th to j-th element
  ll query(int i, int j, int node, int nl, int nr) {
    if (lazy1[node] != 1 or lazy2[node] != 0) updateLazy(node, nl, nr);
    if (j<nl || i>nr) return 0; // change this
    if (i <= nl && nr <= j) return seg[node];
    int mid = (nl + nr) / 2;
    return (query(i, j, 2 * node, nl, mid)+query(i, j, 2 * node + 1, mid + 1, nr))%mod;  // change this
  }
  ll query(int i, int j){ // 1-indexed
    return query(i,j,1,1,n);
  }
};

int n;
int a[100005];
int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout << fixed;
  cout.precision(20);
///////////////////////////////////////////////
  //freopen("input1.txt","r",stdin);
  sf1(n);
  SegLazy SL(n);
  rep(i,1,n+1){
    sf1(a[i]);
    SL.upd3(i,i,a[i]);
  }
  int m;
  sf1(m);
  while(m--){
    int q;
    sf1(q);
    int x,y,v;
    sf2(x,y);
    if(q!=4) sf1(v);
    if(q==1) SL.upd1(x,y,v);
    else if(q==2) SL.upd2(x,y,v);
    else if(q==3) SL.upd3(x,y,v);
    else pf1l(SL.query(x,y));
  }  
}
