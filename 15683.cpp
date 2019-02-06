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

int n,m;
int board_oo[10][10];
vector<pii> cc;
// (x,y)에서 dir 방향으로 진행하면서 벽을 만날때까지 모든 빈 칸을 7로 바꿔버림
void upd(int board[][10], int x, int y, int dir){
  dir %= 4;
  while(1){
    x += dx[dir];
    y += dy[dir];
    if(OOB(x,y,n,m)) break;
    if(board[x][y] == 6) break;
    if(board[x][y] != 0) continue;
    board[x][y] = 7;
  }
}
int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout << fixed;
  cout.precision(20);
  sf2(n,m);
  int mn = 0;
  rep(i,0,n) rep(j,0,m){
    sf1(board_oo[i][j]);
    if(board_oo[i][j] != 0 and board_oo[i][j] != 6)
      cc.push_back({i,j});
    if(board_oo[i][j] == 0) mn++;
  }
  // mn : 최소 크기. 현재는 빈칸의 갯수
  rep(tmp,0,(1<<(2*sz(cc)))){
    int board[10][10];
    rep(i,0,n)rep(j,0,m) board[i][j] = board_oo[i][j];
    int brute = tmp;
    rep(i,0,sz(cc)){
      int x = cc[i].X;
      int y = cc[i].Y;
      int dir = brute & 0x3;
      brute >>= 2;
      if(board[x][y] == 1){
        upd(board,x,y,dir);
      }
      else if(board[x][y] == 2){
        upd(board,x,y,dir);
        upd(board,x,y,dir+2);
      }
      else if(board[x][y] == 3){
        upd(board,x,y,dir);
        upd(board,x,y,dir+1);
      }
      else if(board[x][y] == 4){
        upd(board,x,y,dir);
        upd(board,x,y,dir+1);
        upd(board,x,y,dir+2);
      }
      else if(board[x][y] == 5){
        upd(board,x,y,dir);
        upd(board,x,y,dir+1);
        upd(board,x,y,dir+2);
        upd(board,x,y,dir+3);
      }      
    }
    int val = 0;
    rep(i,0,n)rep(j,0,m) val += (board[i][j]==0);
    if(mn>val)mn=val;
  }
  pf1l(mn); 
}
