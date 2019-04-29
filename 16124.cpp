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

string s;
int mod = 998244353;
int seg[4000005][10];
int lazy[4000005][10]; // lazy : 해당 원소가 무엇으로 바뀌어야 하는가?
int ppow10[1000003];
class SegLazy { // 1-indexed
public:
  //vector<ll> seg, lazy;
  int n;
  SegLazy(int n):n(n) {
  //  seg.resize(4 * n + 4);
  //  lazy.resize(4 * n +4);
  }
  void updateLazy(int node, int nl, int nr) {
    bool isfixed = 1;
    for(int i = 0; i < 10; i++){
      if(lazy[node][i] != i){
        isfixed = 0;
        break;
      }
    }
    if(isfixed) return;
    int tmpseg[10] = {0};
    for(int i = 0; i < 10; i++){
      tmpseg[lazy[node][i]] += seg[node][i];
      tmpseg[lazy[node][i]] %= mod;
    }
    for(int i = 0; i < 10; i++) seg[node][i] = tmpseg[i];
    if (nl != nr) {
      int tmplazy1[10]={}, tmplazy2[10]={};
      for(int i = 0; i < 10; i++){
        tmplazy1[i] = lazy[node][lazy[2*node][i]];
        tmplazy2[i] = lazy[node][lazy[2*node+1][i]];
      }
      for(int i = 0; i < 10; i++){
        lazy[2*node][i] = tmplazy1[i];
        lazy[2*node+1][i] = tmplazy2[i];        
      }
    }
    for(int i = 0; i < 10; i++) lazy[node][i] = i;
  }
  // f -> t in i-th element ~ j-th element
  void update(int i, int j, int f, int t, int node, int nl, int nr) {
    updateLazy(node, nl, nr);
    if (j<nl or i>nr) return;
    if (i <= nl and nr <= j) {
      lazy[node][f] = t;
      updateLazy(node,  nl, nr);
      return;
    }
    int mid = (nl + nr) / 2;
    update(i, j, f, t, 2 * node, nl, mid);
    update(i, j, f, t, 2 * node + 1, mid + 1, nr);
    for(int i = 0; i < 10; i++)
      seg[node][i] = ((ll)ppow10[nr-mid]*seg[2 * node][i] + seg[2 * node + 1][i])%mod;
  }
  void update(int i, int j,int f, int t){ // 1-indexed
    update(i,j,f,t,1,1,n);
  }
  // sum of i-th to j-th element
  int query(int i, int j, int node, int nl, int nr) {
    updateLazy(node, nl, nr);
    if (j<nl || i>nr) return 0;
    if (i <= nl && nr <= j){
      ll tot = 0;
      for(int i = 0; i < 10; i++){
//        pf3l(i,seg[node][i],tot);
        tot += (ll)i*seg[node][i];
      }
      //pf4l(node,nl,nr,tot%mod);
      return tot%mod;
    }
    int mid = (nl + nr) / 2;
    ll ret = 0;
    if(mid+1 <= j){
      ret = query(i, j, 2 * node + 1, mid + 1, nr);
      ret += (ll)ppow10[min(j,nr)-mid]*query(i,j,2*node,nl,mid);
    }
    else ret = query(i,j,2*node,nl,mid);
    //pf4l(node,nl,nr,ret);
    return ret%mod;
  }
  int query(int i, int j){ // 1-indexed
    return query(i,j,1,1,n);
  }
  void init(int node, int nl, int nr){
    for(int i = 0; i < 10; i++) lazy[node][i] = i;
    if(nl == nr){
      seg[node][s[nl-1]-'0'] = 1;
      return;
    }
    int mid = (nl+nr) / 2;
    init(2*node, nl, mid);
    init(2*node+1, mid+1, nr);
    for(int i = 0; i < 10; i++){
      seg[node][i] = ((ll)ppow10[nr-mid]*seg[2*node][i]+seg[2*node+1][i])%mod;
//      pf3l(nr,mid,ppow10[nr-mid]);
//      pf5l(node,nl,nr,i,seg[node][i]);
    }
  }  
};

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout << fixed;
  cout.precision(20);
///////////////////////////////////////////////
  ppow10[0] = 1;
  rep(i,1,1000001){
    ppow10[i] = (ll)ppow10[i-1]*10%mod;
  }
  sf1(s);
  int q;
  sf1(q);
  int n = sz(s);
  SegLazy SS(n);
  SS.init(1,1,n);
  while(q--){
    int q;
    sf1(q);
    if(q==1){
      int i,j,f,t;
      sf4(i,j,f,t);
      SS.update(i,j,f,t);
    }
    else{
      int i,j;
      sf2(i,j);
      pf1l(SS.query(i,j));
    }
  }
}
 
