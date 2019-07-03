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

int n;
vector<pii> adj[200001]; // {idx, cost}
pll d1[200001], d2[200001]; // d1[i], d2[i] : i를 parent로 가지는 subtree에서 최대 길이
pll p1[200001],p2[200001],p3[200001]; // i를 root로 하는 subtree에서 i -> leaf의 최대 길이 3개.(index, 길이)
ll r1[200001]; // i에서 i의 subtree에 속하지 않는 leaf로 가는 최대 길이
ll outside[200001]; // 내 subtree가 아닌 곳에서의 최대 지름
ll ans = 0;
// d1, p1, p2, p3 구함
void dfs1(int cur, int par){
  for(auto e : adj[cur]){
    if(e.X == par) continue;
    dfs1(e.X, cur);
    ll dist = p1[e.X].Y + e.Y;
    if(dist > p1[cur].Y){
      p3[cur] = p2[cur];
      p2[cur] = p1[cur];
      p1[cur] = {e.X,dist};
    }
    else if(dist > p2[cur].Y){
      p3[cur] = p2[cur];
      p2[cur] = {e.X,dist};
    }
    else if(dist > p3[cur].Y)
      p3[cur] = {e.X,dist};

    // e.X를 root로 하는 subtree에서 최대 길이
    ll mx = max(p1[e.X].Y+p2[e.X].Y, d1[e.X].Y);
    //printf("e.X : %d mx : %lld\n",e.X,mx);
    if(mx > d1[cur].Y){
      d2[cur] = d1[cur];
      d1[cur] = {e.X,mx};
    }
    else if(mx > d2[cur].Y)
      d2[cur] = {e.X,mx};
  }
  /*printf("cur : %d, d1 : (%lld, %lld), ", cur,d1[cur].X,d1[cur].Y);
  printf("d2 : (%lld, %lld), ", d2[cur].X,d2[cur].Y);
  printf("p1 : (%lld, %lld), ", p1[cur].X,p1[cur].Y);
  printf("p2 : (%lld, %lld), ", p2[cur].X,p2[cur].Y);
  printf("p3 : (%lld, %lld)\n", p3[cur].X,p3[cur].Y); */
  
}

void dfs2(int cur, int par, ll dist){
  // (cur, e.X)가 끊고싶은 간선
  for(auto e : adj[cur]){
    // dia1 : e.X를 subtree로 하는 곳에서의 지름, dia2 : 바깥부분의 지름
    ll dia1=0, dia2=0;
    dia1 = max(d1[e.X].Y,p1[e.X].Y+p2[e.X].Y);
    if(e.X == par) continue;
    // 1. cur의 subtree 내에 트리의 지름이 존재할 때
    if(e.X == d1[cur].X) dia2 = max(dia2, d2[cur].Y);
    else dia2 = max(dia2, d1[cur].Y);
    if(e.X == p1[cur].X) dia2 = max(dia2, p2[cur].Y+p3[cur].Y);
    else if(e.X == p2[cur].X) dia2 = max(dia2, p1[cur].Y+p3[cur].Y);
    else dia2 = max(dia2, p1[cur].Y+p2[cur].Y);

    if(cur==1){}
    else{     
      // 2. cur가 아예 관여하지 않을 경우
      // 2-1. par조차 안쓰임
      outside[cur] = outside[par];
      //dia2 = max(dia2, outside[par]);
      
      // 2-2. par는 쓰임
      // 2-2-1. d 확인
      if(cur == d1[par].X) outside[cur] = max(outside[cur], d2[par].Y);
      else outside[cur] = max(outside[cur], d1[par].Y);
      // 2-2-2. p 확인
      if(cur == p1[par].X) outside[cur] = max(outside[cur], p2[par].Y+p3[par].Y);
      else if(cur == p2[par].X) outside[cur] = max(outside[cur], p1[par].Y+p3[par].Y);
      else outside[cur] = max(outside[cur], p1[par].Y+p2[par].Y);
      // 2-2-3. r 확인
      if(cur == p1[par].X) outside[cur] = max(outside[cur], r1[par]+p2[par].Y);
      else outside[cur] = max(outside[cur], r1[par]+p1[par].Y);
      
      dia2 = max(dia2, outside[cur]);
      // r 갱신
      r1[cur] = r1[par];
      if(cur == p1[par].X) r1[cur] = max(r1[cur],p2[par].Y);
      else r1[cur] = max(r1[cur],p1[par].Y);
      r1[cur] += dist;

      // 3. cur의 subtree의 leaf와 다른쪽의 leaf의 합일 때
      if(e.X == p1[cur].X) dia2 = max(dia2, p2[cur].Y+r1[cur]);
      else dia2 = max(dia2, p1[cur].Y+r1[cur]);

    }
    //printf("r : %lld, par : %d, cur : %d,  e.X : %d, e.Y : %d, dia1 : %lld, dia2 : %lld, out : %lld\n", r1[cur],par,cur,e.X,e.Y,dia1,dia2,outside[cur]);
    ans = max(ans, dia1+dia2+e.Y);
    dfs2(e.X, cur, e.Y);
  }
}
int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout << fixed;
  cout.precision(20);
///////////////////////////////////////////////
  sf1(n);
  rep(i,0,n-1){
    int a,b,c;
    sf3(a,b,c);
    adj[a].pb({b,c});
    adj[b].pb({a,c});
  }
  dfs1(1,0);
  dfs2(1,0,0);
  cout << ans;
  
}
