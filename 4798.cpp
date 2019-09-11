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

vector<bool> isp(10000001,true);
vector<int> plist;

ull mul(ull a, ull b, ull m){
  return __uint128_t(a)*b%m;
}
ull lpow(ull x, ull y, ull m){
  ull r = 1;
  x %= m;
  while(y){
    if(y&1) r = mul(r,x,m);
    x = mul(x,x,m);
    y >>= 1;
  }
  return r;
}
// 합성수인가 아닌가.
bool MR(ull n, ull a){
  if(a%n==0) return 1;
  int cnt = __builtin_ctzll(n-1);
  ull d = n >> cnt;
  ull p = lpow(a,d,n);
  if(p==1 or p==n-1) return 1;
  while(cnt--){
    p=mul(p,p,n);
    if(p==n-1) return 1;
  }
  return 0;
}
/*
+------------+---------+--------------------------------------------------+
|   Range    |  Usage  |             a (a % N == 0 is prime)              |
+------------+---------+--------------------------------------------------+
| 1050535501 | <= 10^9 | 336781006125, 9639812373923155                   |
| 4759123141 | <= 2^32 | 2, 7, 61                                         |
|      ?     | <= 2^64 | 2, 325, 9375, 28178, 450775, 9780504, 1795265022 |
+------------+---------+--------------------------------------------------+
*/

bool isprime(ll n){
  if(n < 10000001) return isp[n];
  if(n <= 2) return n == 2;
  if(!(n&1)) return 0;
  if(n%3==0 or n%5==0 or n%7==0 or n%11==0) return 0;
  for(int p : { 2, 325, 9375, 28178, 450775, 9780504, 1795265022}){
    if(!MR(n,p)){
      return 0;
    }
  }
  return 1;
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout << fixed;
  cout.precision(20);
///////////////////////////////////////////////
  //freopen("output.txt","w",stdout);
  isp[0] = false;
  isp[1] = false;
  for(int i = 2; i*i < 10000001; i++){
    if(!isp[i]) continue;
    for(int j = i*i; j < 10000001; j+=i) isp[j] = false;
  }
  for(int i = 2; i <= 1000000; i++){
    if(isp[i]) plist.pb(i);
  }
  for(int tc = 1; ; tc++){
    ll a,b,l,u;
    sf1(a);
    if(a==0) break;
    sf3(b,l,u);
    if(__gcd(a,b) != 1){
      int cnt = 0;
      if(l == 0 and isprime(b)) cnt++;
      else if(l <= 1 and u >= 1 and isprime(a+b)) cnt++;
      cout << "Case " << tc << ": " << cnt << '\n';
      continue;
    }
    vector<bool> state(u-l+1,true);
    state[0] = isprime(a*l+b);
    if(l!=u) state[1] = isprime(a*l+a+b);
    for(auto p : plist){
      if(1ll*p*p > a*u+b) break;
      if(a%p == 0) continue;
      // a*factor = b mod p
      //cout << "prime " << p << "\n";
      ll factor = (p-b%p)*EXGCD(a, p).X%p;
      if(factor < 0) factor += p;      
      ll st = l;
      st += factor - (st % p);
      if(st < l) st += p;
      if(a*st+b == 0) st += p;
      if(a*st+b == p) st += p;
      while(st <= u){
        //cout << a*st+b <<  " false\n";
        state[st-l] = false;
        st += p;
      }
    }
    //for(int i = 0; i < u-l+1; i++){
    //  cout << a*(i+l)+b << ' ' << state[i] << '\n';
    //}
    cout << "Case " << tc << ": " << count(all(state), true) << '\n';
  }
}
