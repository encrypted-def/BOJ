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
int N,M,Q;
ti3 edge[100003];
pii query[100003];
int st[100003],en[100003], mid[100003];
pii ans[100003];
vi p;
int UF_find(int x){
  if(p[x]<0) return x;
  return p[x] = UF_find(p[x]);
}
bool UF_union(int a, int b){
  a = UF_find(a);
  b = UF_find(b);
  if(a==b) return 0;
  if(p[b] < p[a]) swap(a,b);
  p[a] += p[b];
  p[b] = a;
  return 1;
}


int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0);
  sf2(N,M);
  p.resize(N+1,-1);
  for(int i = 0; i < M; i++){
    int a,b,c;
    sf3(a,b,c);
    edge[i] = {c,a,b};
  }
  sort(edge,edge+M);
  sf1(Q);
  rep(i,0,Q){
    sf2(query[i].X,query[i].Y);
    assert(query[i].X != query[i].Y);
  }
  fill(st,st+Q,0);
  fill(en,en+Q,M-1);
  fill(mid,mid+Q,(M-1)>>1);
  // 애초에 연결이 안된 경우를 확인
  for(int i = 0; i < M; i++) UF_union(get<1>(edge[i]), get<2>(edge[i]));
  for(int i = 0; i < Q; i++){
    if(query[i].X == query[i].Y or UF_find(query[i].X) != UF_find(query[i].Y)){
      st[i] = -1;
      en[i] = -1;
      mid[i] = -1;
      ans[i] = {-1,-1};
    }
  }
  bool isDone = 0;
  while(!isDone){

    fill(all(p),-1);
    isDone = 1;
    pii Qsort[Q];
    rep(i,0,Q)
      Qsort[i] = {mid[i],i};
    sort(Qsort,Qsort+Q);
    int curEdge = 0;
    rep(i,0,Q){
      int idx = Qsort[i].Y;
      if(ans[idx].X == -1) continue;
      while(curEdge < M and curEdge <= mid[idx]){
        UF_union( get<1>(edge[curEdge]),get<2>(edge[curEdge]) );
        curEdge++;
      } 
      if(st[idx] == en[idx]){
        ans[idx] = {get<0>(edge[st[idx]]), -p[UF_find(query[idx].X)]};
        continue;
      }
      if(UF_find(query[idx].X) == UF_find(query[idx].Y))
        en[idx] = mid[idx];
      else
        st[idx] = mid[idx]+1;

      mid[idx] = (st[idx]+en[idx])>>1;
      isDone = 0;      
    }
  }
  rep(i,0,Q){
    if(query[i].X == query[i].Y) pf2l(0,1);
    else if(ans[i].X == -1) pf1l(-1);
    else pf2l(ans[i].X,ans[i].Y);
  }
}
