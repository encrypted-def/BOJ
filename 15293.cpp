# pragma GCC optimize ("O3")
# pragma GCC optimize ("Ofast")
# pragma GCC optimize ("unroll-loops")
//# pragma GCC target("sse,sse2,sse3,ssse3,sse4,avx,avx2")
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


ull INV(ull a, int cnt) {
  ull ret = 1;
  for(int i = 0; i < cnt; i++, a*=a) ret*=a;
  if(cnt != 63) ret %= ((ull)1 << (cnt+1));
  return ret;
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

int n;
ull b[64];
ull s;

void mitm(){
  int left = n/2;
  int right = n-left;
  vector<pair<ull,int> > l;
  rep(mask,0,(1<<left)){
    ull tot = 0;
    rep(i,0,left){
      if(mask & (1<<i)) tot += b[left-1-i];
    }
    l.pb({tot, mask});
  }
  sort(all(l));
  rep(mask,0,(1<<right)){
    ull tot = 0;
    rep(i,0,right){
      if(mask & (1<<i)) tot += b[n-1-i];
    }
    auto it = lower_bound(all(l),make_pair((ull)(s-tot),-1));
    if(it->X+tot == s){
      int mask1 = it->Y;
      for(int i = left-1; i >= 0; i--){
        if(mask1 & (1<<i)) cout << 1;
        else cout << 0;
      }
      for(int i = right-1; i >= 0; i--){
        if(mask & (1<<i)) cout << 1;
        else cout << 0;        
      }
      return;
    }
  }
}

int ans[70];
bool chk(ull factor){
  ull tot = 0;
  ull BB = (ull)-1;
  //if(b[0]*factor < (1<<20) and b[1]*factor < (1<<20))
  //  rep(i,0,n) pf1(b[i]*factor);
  //pf0l();
  rep(i,0,n){
    ull cur = b[i]*factor;
    if(tot >= cur) return false;
    if(cur > BB - tot) return false;
    tot += cur;    
  }
  fill(ans,ans+n,0);
  ull val = s*factor;
  for(int i = n-1; i >= 0; i--){
    //pf2l("now val : ", val);
    if(val >= b[i]*factor){
      val -= b[i]*factor;
      ans[i] = 1;
    }
  }
  rep(i,0,n) cout << ans[i];
  //rep(i,0,n){
  //  pf1l(b[i]*factor);
  //}
  
  return true;
}
int main(void) {
  //ios::sync_with_stdio(false);
  cin.tie(0);
  cout << fixed;
  cout.precision(20);
///////////////////////////////////////////////
  sf1(n);
  //n = 50;
  //ull r = ((ull)rand()<<50)+((ull)rand()<<10)+(rand()<<7)+(rand()<<5)+rand();
  //pf2l("r : ", r);
  rep(i,0,n){
    sf1(b[i]);
    //b[i] = ((ull)1)<<i;
    //b[i] = b[i]*r;
    //pf1l(b[i]);
  }
  sf1(s);
  //s = 67*r;
  if(n==1){
    if(s==0)pf1l(0);
    else pf1l(1);
    return 0;
  }
  if(n <= 42){
    mitm();
    return 0;
  }
  

  int trail_zero = 0;
  ull tmp = b[0];
  while(!(tmp&1)){tmp>>=1; trail_zero++;}
  ull added = ((ull)1<<trail_zero);
  ull factor = INV(b[0]>>trail_zero, 63-trail_zero);
  ull ff = factor;
  //pf2l("trail_zero : ", trail_zero);
  //pf2l("factor : ", factor);
  rep(z,0,1<<(64-n-trail_zero)){
    rep(k,0,(1<<trail_zero)){
      ull vv = ff+((ull)1<<(64-trail_zero))*k;
      if(chk(vv)) return 0;    
      //if(z<10) pf5l(z,k,vv,vv*b[0],vv*b[1]);
    }
    ff += 2*factor;    
  }  
}
