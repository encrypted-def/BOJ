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
int arr[100005];
int tot[100005];
ti3 seg[400005]; // {구간 내에서 최대 합, 가장 왼쪽의 원소를 포함한 최대 합, 가장 오른쪽의 원소를 포함한 최대 합}
int INF = 0x3f3f3f3f;

int lis1[100005],lis2[100005]; // lis1 : 왼쪽부터 채움, lis2 : 오른쪽부터 채움
void init(int num, int a, int b){
  lis1[a] = arr[a];
  rep(i,a+1,b+1)
    lis1[i] = arr[i] + max(lis1[i-1],0);
  
  lis2[b] = arr[b];
  for(int i = b-1; i >= a; i--)
    lis2[i] = arr[i]+max(lis2[i+1],0);
  
  seg[num] = {*max_element(lis1+a,lis1+b+1), lis2[a],lis1[b]};
  
  if(a != b){
    int mid = (a+b)/2;
    init(2*num,a,mid);
    init(2*num+1,mid+1,b);
  }
}

ti3 query(int i, int j, int num, int a, int b){
  if(a > j or b < i) return {-INF,-INF,-INF};
  if(i <= a and b <= j) return seg[num];
  int mid = (a+b)/2;
  ti3 val1 = query(i,j,2*num,a,mid);
  ti3 val2 = query(i,j,2*num+1,mid+1,b);
  int m1,l1,r1,m2,l2,r2;
  tie(m1,l1,r1) = val1;
  tie(m2,l2,r2) = val2;
  ti3 ret;
  get<0>(ret) = max(max(m1,m2),r1+l2);
  get<1>(ret) = max(l1,tot[mid]-tot[a-1]+l2);
  get<2>(ret) = max(r2,tot[b]-tot[mid]+r1);
  return ret;
}
int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout << fixed;
  cout.precision(20);
///////////////////////////////////////////////
  sf1(n);
  rep(i,1,n+1){
    sf1(arr[i]);
    tot[i] = tot[i-1]+arr[i];
  }
  init(1,1,n);
  int m;
  sf1(m);
  while(m--){
    int a,b;
    sf2(a,b);
    pf1l(get<0>(query(a,b,1,1,n)));
  } 
}
 
