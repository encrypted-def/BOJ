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


int l[6000006];
int r[6000006];
int val[6000006];
int root[100006]; // pst의 시작점
int insert_idx;
int init(int st, int en){
  //pf2l(st,en);
  int cur = insert_idx;
  insert_idx++;
  val[cur] = 0;
  l[cur] = -1; r[cur] = -1;
  if(st==en) return cur;
  int mid = (st+en)/2;
  l[cur] = init(st,mid);
  r[cur] = init(mid+1,en);
  return cur;
}
// 현재 root[i]에 y=k인 점을 넣고 있음
void insert(int i, int k){
  val[insert_idx] = val[root[i]]+1;
  l[insert_idx] = l[root[i]];
  r[insert_idx] = r[root[i]];
  root[i] = insert_idx;
  insert_idx++;
  int st = 0,en=100000;
  int cur = root[i];
  while(1){
    int mid = (st+en)/2;    
    // left에 새로운 노드 생성
    if(k <= mid){      
      val[insert_idx] = val[l[cur]]+1;
      l[insert_idx] = l[l[cur]];
      r[insert_idx] = r[l[cur]];    
      l[cur] = insert_idx;
      insert_idx++;
      cur = l[cur];
      en = mid;
    }
    else{
      val[insert_idx] = val[r[cur]]+1;
      l[insert_idx] = l[r[cur]];
      r[insert_idx] = r[r[cur]];    
      r[cur] = insert_idx;
      insert_idx++;
      cur = r[cur];
      st = mid+1;
    }
    if(st==mid and mid==en) break;
  }  
}
// x좌표가 x 이하인 점들에서 y가 ymin이상 ymax이하인 점 개수. idx번째 노드는 st부터 en까지 커버함
int query(int x, int idx, int st, int en, int ymin, int ymax){
  if(ymin <= st and en <= ymax) return val[idx];
  if(ymin > en or ymax < st) return 0;
  int mid = (st+en)/2;
  return query(x, l[idx], st, mid, ymin, ymax)+query(x,r[idx],mid+1,en,ymin,ymax);
}
// root[i]는 x가 i 이하인 점들에 대해 해당 구간에 점이 몇 개 있는지를 나타내는 segment tree
int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout << fixed;
  cout.precision(20);
///////////////////////////////////////////////
  int t;
  sf1(t);
  while(t--){
    int n,m;
    insert_idx = 1; // new node idx
    init(0,100000);
    root[0] = 1;
    sf2(n,m);
    vector<pii> pt(n);
    rep(i,0,n) sf2(pt[i].X,pt[i].Y);
    sort(all(pt));
    int curX = 0;
    rep(i,0,n){
      if(curX < pt[i].X){
        while(curX < pt[i].X){
          root[curX+1] = root[curX];
          curX++;
        }
      }
      insert(curX, pt[i].Y);               
    }
    for(int i = curX+1; i <= 100000; i++) root[i] = root[curX];
    int ans = 0;
    while(m--){
      int a,b,c,d;
      sf4(a,b,c,d);
      ans += query(b,root[b],0,100000,c,d);
      if(a != 0) ans -= query(a-1,root[a-1],0,100000,c,d);
    }
    pf1l(ans);    
  } 
}
