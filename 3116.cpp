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
int dx[9] = {0,-1,0,1,1,1,0,-1,-1};
int dy[9] = {0,1,1,1,0,-1,-1,-1,0};
int n;
ti3 bac[5007];
vector<ti3> meet;
int state[5006];
int collide_time(int i, int j){
  int x1,y1,dir1;
  int x2,y2,dir2;
  tie(x1,y1,dir1) = bac[i];
  tie(x2,y2,dir2) = bac[j];
  int diffx = dx[dir1]-dx[dir2];
  int diffy = dy[dir1]-dy[dir2];
  if(diffx == 0 and diffy == 0) return -1;
  if(diffx == 0 and x1 != x2) return -1;
  if(diffy == 0 and y1 != y2) return -1;
  if(diffx == 0){
    if((y1-y2)%diffy != 0) return -1;
    return abs((y1-y2)/diffy);
  }
  if(diffy == 0){
    if((x1-x2)%diffx != 0) return -1;
    return abs((x1-x2)/diffx);
  }
  if ((y1 - y2) % diffy != 0) return -1;
  if ((x1 - x2) % diffx != 0) return -1;
  if( abs((y1-y2)/diffy) != abs((x1-x2)/diffx) ) return -1;
  return abs((x1-x2)/diffx);
}
int main(void) {
//  ios::sync_with_stdio(false);
//  cin.tie(0);
  cout << fixed;
  cout.precision(20);
///////////////////////////////////////////////
  sf1(n);
  rep(i,0,n){
    int a,b,c;
    sf3(a,b,c);
    bac[i] = {a,b,c};
  }
  rep(i,0,n){
    rep(j,i+1,n){
      int t = collide_time(i,j);
      if(t != -1) meet.pb({t,i,j});
    }
  }
  sort(all(meet));
  int highrank = -1;
  int firstmeet = -1;
  int idx = 0;
  int cnt[5003]={0,};
  while(idx < sz(meet)){
    vi occur;
    int st = idx;
    while(idx < sz(meet) and get<0>(meet[idx]) == get<0>(meet[st])) idx++;
    int en = idx-1;
    rep(i,st,en+1){
      cnt[get<1>(meet[i])]++;
      cnt[get<2>(meet[i])]++;      
      occur.pb(get<1>(meet[i]));
      occur.pb(get<2>(meet[i]));      
    }
    sort(all(occur));
    occur.erase(unique(all(occur)),occur.end());
    for(auto elem : occur){
      if(highrank < cnt[elem]+1){
        highrank = cnt[elem]+1;
        firstmeet = get<0>(meet[idx-1]);
      }
      cnt[elem] = 0;
    }
  }
  pf1l(highrank);
  pf1l(firstmeet);
  
}
