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

// x=a[i] mod m[i]를 만족하는 x를 반환
// m은 쌍으로 서로소이어야 함
// m들끼리의 곱이 ll 범위를 넘어갈 경우 사용 불가
ll crt(vector<ll>& a, vector<ll>& m){
  int n = m.size();
  ll ret = a[0];
  ll mod = m[0];
  for(int i = 1; i < n; i++){
    ll m1 = mod;
    mod *= m[i];
    ll m2inv = INV(m[i],m1);
    ll m1inv = INV(m1,m[i]);
    ret = (ret*m[i]%mod*m2inv%mod + a[i]*m1%mod*m1inv%mod) % mod;
  }
  return ret;
}

int main(void) {
 // ios::sync_with_stdio(false);
 // cin.tie(0);
  cout << fixed;
  cout.precision(20);
///////////////////////////////////////////////
  ll n,k,m;
  sf3(n,k,m);
  k = min(k,n-k);
  if(k==0 or n==1){
    pf1(1);
    return 0;
  }
  vi factor;
  int tmpm = m;
  for(ll p = 2; p*p <= tmpm; p++){
    if(tmpm%p == 0){
      factor.pb(p);
      while(tmpm%p == 0){
        tmpm /= p;
      }
    }
  }
  if(tmpm != 1) factor.pb(tmpm);
  vector<pll> val(sz(factor)); // i번째 소수에 대해 {소수의 갯수, 소수로 나눈 나머지}를 저장할 계획
  vi num(sz(factor)); // 각 factor가 n comb m에 몇 개 있는지
  ll ans = 1;
  rep(a,n-k+1,n+1){
    ll tmp = a;
    rep(i,0,sz(factor)){
      int p = factor[i];
      while(tmp % p == 0){
        tmp /= p;
        num[i]++;
      }
    }
    ans = (ans*tmp)%m;
  }
  rep(a,1,k+1){
    ll tmp = a;
    rep(i,0,sz(factor)){
      int p = factor[i];
      while(tmp % p == 0){
        tmp /= p;
        num[i]--;
      }
    }
    ans = (ans*INV(tmp,m))%m;
  }
  rep(i,0,sz(factor)){
    ans = ans*POW(factor[i],num[i],m)%m;
  }
  pf1l(ans);
}
