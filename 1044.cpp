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

int N;
ll s1[40],s2[40];
int cntBit(ll a){
  int ret = 0;
  while(a){
    if(a&1) ret++;
    a >>= 1;
  }
  return ret;
}
map<pll,ll> M1;
map<pll,ll> M2;
int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0);
  sf1(N);
  rep(i,0,N) sf1(s1[i]);
  rep(i,0,N) sf1(s2[i]);
  int len1 = N/2;
  int len2 = N-len1;
  rep(i,0,1<<len1){
    ll val = 0;
    rep(j,0,len1){
      if(i & (1<<(len1-1-j))){
        val += s2[j];
      }
      else
        val -= s1[j];
    }
    if(M1.find({val, cntBit(i)}) != M1.end())
      M1[{val, cntBit(i)}] = min(M1[{val, cntBit(i)}],(ll)i);
    else
      M1[{val, cntBit(i)}] = i;
  }
  rep(i,0,1<<len2){
    ll val = 0;
    rep(j,0,len2){
      if(i & (1<<(len2-1-j)))
        val += s2[len1+j];
      else
        val -= s1[len1+j];
    }
    if(M2.find({val, cntBit(i)}) != M2.end())
      M2[{val, cntBit(i)}] = min(M2[{val, cntBit(i)}],(ll)i);
    else
      M2[{val, cntBit(i)}] = i;

  }
  vector<tl3> list1;
  vector<tl3> list2;
  ll INF = 0x3f3f3f3f3f3f3f3f;  
  for(auto t : M1) list1.pb({t.X.Y,t.X.X,t.Y});
  for(auto t : M2){
    list2.pb({t.X.Y,t.X.X,t.Y});
  }
  rep(i,0,40){
    list2.pb({i,-INF,0});
    list2.pb({i,INF,0});    
  }
  sort(all(list1));
  sort(all(list2));
  //for(auto t : list1) pf3l(get<0>(t),get<1>(t),get<2>(t));
  //pf1l("----------------");
  //for(auto t : list2) pf3l(get<0>(t),get<1>(t),get<2>(t));
  ll diff = INF;
  ll select = INF;
  for(auto e1 : list1){
    if(get<0>(e1) > N/2) continue;
    auto e2 = *lower_bound(all(list2),make_tuple(N/2-get<0>(e1),-get<1>(e1),get<2>(e1)));
    ll curDiff = abs(get<1>(e1) + get<1>(e2));
    ll curSelect = (get<2>(e1) << len1) | get<2>(e2);
    if(diff > curDiff or (diff==curDiff and select > curSelect)){
      diff = curDiff;
      select = curSelect;
    }
    e2 = *prev(lower_bound(all(list2),make_tuple(N/2-get<0>(e1),-get<1>(e1),get<2>(e1))));
    curDiff = abs(get<1>(e1) + get<1>(e2));
    curSelect = (get<2>(e1) << len1) | get<2>(e2);
    if(diff > curDiff or (diff==curDiff and select > curSelect)){
      diff = curDiff;
      select = curSelect;
    }
  }
  rep(i,0,N){
    if(select & (1ll<<(N-1-i))) pf1(2);
    else pf1(1);

  }
}
