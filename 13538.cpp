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

class Node{
public:
  int v,l,r;
  Node(int v, int l, int r):v(v), l(l), r(r) {}
};

class PST{
public:
  vector<Node> node;
  vector<int> head;
  int nsz = 1; // 총 노드의 갯수
  int hsz = 1; // head의 갯수(=A의 원소의 갯수)
  PST(int nodenum, int querynum):node(nodenum+1, Node(0,0,0)), head(querynum+1){}
  void query1(int x){ // 배열 A의 끝에 x를 추가한다.
    head[hsz] = nsz;
    node[nsz] = node[head[hsz-1]];
    node[nsz].v++;
    int cur = nsz;
    nsz++;
    hsz++;
    for(int i = 18; i >= 0; i--){
      if(!(x & (1<<i))){ // i번째 bit가 0일 경우 
        node[nsz] = node[node[cur].l];
        node[nsz].v++;
        node[cur].l = nsz;
        cur = nsz;
        nsz++;
      }
      else{
        node[nsz] = node[node[cur].r];
        node[nsz].v++;
        node[cur].r = nsz;
        cur = nsz;
        nsz++;
      }     
    }
  }
  int query2(int l, int r, int x){ // l~r번째 수 중에서 x와 xor한 값이 가장 큰 y를 찾아 출력한다.
    int pos1 = head[l-1];
    int pos2 = head[r];
    int ret = 0;
    for(int i = 18; i >= 0; i--){
      if(node[node[pos1].l].v  == node[node[pos2].l].v){
        ret |= (1<<i);
        pos1 = node[pos1].r;
        pos2 = node[pos2].r;
      }
      else if(node[node[pos1].r].v  == node[node[pos2].r].v){
        pos1 = node[pos1].l;
        pos2 = node[pos2].l;
      }
      else if(!(x & (1<<i))){
        ret |= (1<<i);
        pos1 = node[pos1].r;
        pos2 = node[pos2].r;        
      }
      else{
        pos1 = node[pos1].l;
        pos2 = node[pos2].l;        
      }      
    }
    return ret;
  }
  void query3(int k){ // A의 마지막 k개를 제거한다
    hsz -= k;
  }
  int query4(int l, int r, int x){ // l~r 중에서 x보다 작거나 같은 원소의 갯수
    int pos1 = head[l-1];
    int pos2 = head[r];
    int ret = 0;
    for(int i = 18; i >= 0; i--){
      if(x >= (1<<i)){
        ret += node[node[pos2].l].v-node[node[pos1].l].v;
        pos1 = node[pos1].r;
        pos2 = node[pos2].r;        
        x -= (1<<i);
      }
      else{
        pos1 = node[pos1].l;
        pos2 = node[pos2].l;
      }
    }
    ret += node[pos2].v-node[pos1].v;
    return ret;
  }
  int query5(int l, int r, int x){ // l~r 중에서 x번째로 작은 수
    int pos1 = head[l-1];
    int pos2 = head[r];
    int ret = 0;
    for(int i = 18; i >= 0; i--){
      if(node[node[pos2].l].v-node[node[pos1].l].v >= x){
        pos1 = node[pos1].l;
        pos2 = node[pos2].l;
      }
      else{
        x -= (node[node[pos2].l].v-node[node[pos1].l].v);
        pos1 = node[pos1].r;
        pos2 = node[pos2].r;
        ret |= (1<<i);
      }
    }
    return ret;
  }
};

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout << fixed;
  cout.precision(20);
///////////////////////////////////////////////
  int m;
  sf1(m);
  PST pst(10000000,500000);
  while(m--){
    int q;
    sf1(q);
    if(q==1){
      int x;
      sf1(x);
      pst.query1(x);
    }
    if(q==2){
      int l,r,x;
      sf3(l,r,x);
      pf1l(pst.query2(l,r,x));
    }
    if(q==3){
      int k;
      sf1(k);
      pst.query3(k);
    }
    if(q==4){
      int l,r,x;
      sf3(l,r,x);
      pf1l(pst.query4(l,r,x));
    }
    if(q==5){
      int l,r,k;
      sf3(l,r,k);
      pf1l(pst.query5(l,r,k));
    }    
  }
}
