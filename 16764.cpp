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
typedef tuple<int, int, int, int, int> ti5;
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

int flavor[50003][5];
vi p1;
vl p2;
vl p3;
vector<pll> p4;
vector<pll> p5;
int n;
ll m = 1000001;
ll conv2(ll a, ll b){
  return m*a+b;
}
ll conv3(ll a, ll b, ll c){
  return m*m*a+m*b+c;
}
pll conv4(ll a, ll b, ll c, ll d){
  return {m*a+b, m*c+d};
}
pll conv5(ll a, ll b, ll c, ll d, ll e){
  return {m*m*a+m*b+c, m*d+e};
}
int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout << fixed;
  cout.precision(20);
///////////////////////////////////////////////
  cin >> n;
  for(int i = 0; i < n; i++){
    int a[5];
    for(int j = 0; j < 5; j++) sf1(a[j]);
    sort(a,a+5);
    rep(j,0,5) flavor[i][j] = a[j];
    p5.pb(conv5(a[0],a[1],a[2],a[3],a[4]));
    p1.pb(a[0]);
    p1.pb(a[1]);
    p1.pb(a[2]);
    p1.pb(a[3]);
    p1.pb(a[4]);
    p4.pb(conv4(a[0],a[1],a[2],a[3]));
    p4.pb(conv4(a[0],a[1],a[2],a[4]));
    p4.pb(conv4(a[0],a[1],a[3],a[4]));
    p4.pb(conv4(a[0],a[2],a[3],a[4]));
    p4.pb(conv4(a[1],a[2],a[3],a[4]));
    int select[5] = {0,0,0,1,1};
    do{
      int a2[2];
      int i2 = 0;
      int a3[3];
      int i3 = 0;
      rep(j,0,5){
        if(select[j] == 0) a3[i3++] = a[j];
        else a2[i2++] = a[j];
      }
      p2.pb(conv2(a2[0],a2[1]));
      p3.pb(conv3(a3[0],a3[1],a3[2]));
    }while(next_permutation(select,select+5));
  }
  sort(all(p1));
  sort(all(p2));
  sort(all(p3));
  sort(all(p4));    
  sort(all(p5));
  ll tot = 0;
  //pfvecl(p1);
  rep(i,0,n){
    int cnt = n;
    rep(j,0,5){
      cnt -= (upper_bound(all(p1), flavor[i][j]) - lower_bound(all(p1), flavor[i][j]));
      //pf1l((upper_bound(all(p1), flavor[i][j]) - lower_bound(all(p1), flavor[i][j])));
      int tmp[4];
      int ii = 0;
      rep(k,0,5){
        if(k != j) tmp[ii++] = flavor[i][k];
      }
      auto val = conv4(tmp[0],tmp[1],tmp[2],tmp[3]);
      cnt += (upper_bound(all(p4), val) - lower_bound(all(p4), val));
    }
    int select[5] = {0,0,0,1,1};
    do{
      int a2[2];
      int i2 = 0;
      int a3[3];
      int i3 = 0;
      rep(j,0,5){
        if(select[j] == 0) a3[i3++] = flavor[i][j];
        else a2[i2++] = flavor[i][j];
      }
      auto val2 = conv2(a2[0],a2[1]);
      auto val3 = conv3(a3[0],a3[1],a3[2]);
      cnt += (upper_bound(all(p2), val2) - lower_bound(all(p2), val2));
      cnt -= (upper_bound(all(p3), val3) - lower_bound(all(p3), val3));
    }while(next_permutation(select,select+5));
    auto val5 = conv5(flavor[i][0],flavor[i][1],flavor[i][2],flavor[i][3],flavor[i][4]);
    cnt -= (upper_bound(all(p5), val5) - lower_bound(all(p5), val5));
    tot += cnt;
  }
  pf1l(tot/2); 
}


