# pragma GCC optimize ("O3")
# pragma GCC optimize ("Ofast")
# pragma GCC optimize ("unroll-loops")

#include <bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>

#pragma warning(disable:4996)
#pragma comment(linker, "/STACK:336777216")

using namespace std;
//using namespace __gnu_pbds;

typedef long long ll;
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
//typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>ordered_set;


const int ddx[8] = { 0,0,1,1,1,-1,-1,-1 }, ddy[8] = { 1,-1,1,0,-1,1,0,-1 };
const int INF = 0x7f7f7f7f;
const ll INF_LL = 0x7f7f7f7f7f7f7f7f;
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
int N, M;
char board[11][11];
pii red, blue, hole;
int ans = INF;
const int dx[4] = { -1,0,1,0 };
const int dy[4] = { 0,-1,0,1 };
bool cmp(pii a, pii b, int dir) {
	if (dir == 0) return a.X < b.X; // 위
	if (dir == 1) return a.Y < b.Y; // 왼
	if (dir == 2) return a.X > b.X; // 아래
	if (dir == 3) return a.Y > b.Y; // 오른
}
void recursion(int dir, int depth) {
	char boardbak[11][11];
	rep(i, 0, N) rep(j, 0, M) boardbak[i][j] = board[i][j];
	pii redbak, bluebak;
	redbak = red; bluebak = blue;
	if (cmp(red, blue, dir)) {
		bool redout = false;
		board[red.X][red.Y] = '.';
		while (board[red.X + dx[dir]][red.Y + dy[dir]] == '.') {
			red.X += dx[dir]; red.Y += dy[dir];
		}
		if (make_pair(red.X+dx[dir], red.Y+dy[dir]) == hole) {
			redout = true;
		}
		else {
			board[red.X][red.Y] = 'R';
		}
		board[blue.X][blue.Y] = '.';
		while (board[blue.X+dx[dir]][blue.Y+dy[dir]] == '.') {
			blue.X += dx[dir]; blue.Y += dy[dir];
		}
		if (make_pair(blue.X +dx[dir], blue.Y+dy[dir]) == hole) {
			rep(i, 0, N) rep(j, 0, M) board[i][j] = boardbak[i][j];
			red = redbak; blue = bluebak;
			return;
		}
		if (redout) {
			ans = min(ans, depth);
			rep(i, 0, N) rep(j, 0, M) board[i][j] = boardbak[i][j];
			red = redbak; blue = bluebak;
			return;
		}
		board[blue.X][blue.Y] = 'B';
	}
	else {
		board[blue.X][blue.Y] = '.';
		while (board[blue.X+dx[dir]][blue.Y+dy[dir]] == '.') {
			blue.X += dx[dir]; blue.Y += dy[dir];
		}
		if (make_pair(blue.X+dx[dir], blue.Y+dy[dir]) == hole) {
			rep(i, 0, N) rep(j, 0, M) board[i][j] = boardbak[i][j];
			red = redbak; blue = bluebak;
			return;
		}
		board[blue.X][blue.Y] = 'B';
		board[red.X][red.Y] = '.';
		while (board[red.X+dx[dir]][red.Y+dy[dir]] == '.') {
			red.X += dx[dir]; red.Y += dy[dir];
		}
		if (make_pair(red.X+dx[dir], red.Y+dy[dir]) == hole) {
			ans = min(ans, depth);
			rep(i, 0, N) rep(j, 0, M) board[i][j] = boardbak[i][j];
			red = redbak; blue = bluebak;
			return;
		}
		board[red.X][red.Y] = 'R';
	}
	if (red == redbak && blue == bluebak) {
		rep(i, 0, N) rep(j, 0, M) board[i][j] = boardbak[i][j];
		red = redbak; blue = bluebak;
		return;
	}
	if (depth == 10) {
		rep(i, 0, N) rep(j, 0, M) board[i][j] = boardbak[i][j];
		red = redbak; blue = bluebak;
		return;
	}
	rep(dir, 0, 4) recursion(dir, depth + 1);
	rep(i, 0, N) rep(j, 0, M) board[i][j] = boardbak[i][j];
	red = redbak; blue = bluebak;
}
int main(void) {
	int a, b, c;
	cin.tie(0);
	sf2(N, M);
	rep(i, 0, N) sf1(board[i]);
	rep(i, 0, N) {
		rep(j, 0, M) {
			if (board[i][j] == 'R') red = { i,j };
			if (board[i][j] == 'B') blue = { i,j };
			if (board[i][j] == 'O') hole = { i,j };

		}
	}
	rep(dir, 0, 4) recursion(dir, 1);
	if (ans == INF) ans = -1;
	pf1l(ans);
}
