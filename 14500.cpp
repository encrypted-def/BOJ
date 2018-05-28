# pragma GCC optimize ("O3")
# pragma GCC optimize ("Ofast")
# pragma GCC optimize ("unroll-loops")

#include <bits/stdc++.h>

#pragma warning(disable:4996)
#pragma comment(linker, "/STACK:336777216")
using namespace std;
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
int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };
int ddx[8] = { 0,0,1,1,1,-1,-1,-1 }, ddy[8] = { 1,-1,1,0,-1,1,0,-1 };
ll MOD = 1000000000;
ll POW(ll a, ll b, ll MMM = MOD) { ll ret = 1; for (; b; b >>= 1, a = (a*a) % MMM)if (b & 1)ret = (ret*a) % MMM; return ret; }
ll GCD(ll a, ll b) { return b ? GCD(b, a%b) : a; }
ll LCM(ll a, ll b) { if (a == 0 || b == 0)return a + b; return a * (b / GCD(a, b)); }
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
#define pb(x) push_back(x)
#define all(x) (x).begin(), (x).end()
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

vector< vector<pii> > position;
void add_position() {
	vector<pii> cand = { {0,0},{0,1},{0,2},{1,0},{1,1},{1,2},{2,0},{2,1},{2,2} };
	vector<bool> select = { 0,0,0,0,0,1,1,1,1 };
	do {
		bool isVisited[3][3] = { 0, };
		for (int i = 0; i < 9; i++) {
			vi idx;
			if (select[i]) {
				qi Q;
				Q.push(i);
				isVisited[i / 3][i % 3] = true;
				while (!Q.empty()) {
					int cur = Q.front(); Q.pop();
					int x = cur / 3;
					int y = cur % 3;
					idx.pb(cur);
					rep(dir, 0, 4) {
						int nX = x + dx[dir];
						int nY = y + dy[dir];
						if (OOB(nX, nY, 3, 3) || !select[3*nX+nY] || isVisited[nX][nY]) continue;
						isVisited[nX][nY] = true;
						Q.push(3 * nX + nY);
					}
				}
				if (idx.size() == 4)
					position.pb(vector<pii>({ cand[idx[0]],cand[idx[1]], cand[idx[2]], cand[idx[3]] }));
				break;
			}
		}
	} while (next_permutation(all(select)));
}
int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0);
	add_position();
	int N, M;
	int board[505][505];
	sf2(N, M);
	rep(i, 0, N) rep(j, 0, M) sf1(board[i][j]);
	int tot = 0;
	rep(i, 0, N) {
		rep(j, 0, M - 3) {
			int s = board[i][j] + board[i][j + 1] + board[i][j + 2] + board[i][j + 3];
			if (tot < s) tot = s;
		}
	}
	rep(i, 0, N-3) {
		rep(j, 0, M) {
			int s = board[i][j] + board[i+1][j] + board[i+2][j] + board[i+3][j];
			if (tot < s) tot = s;
		}
	}
	rep(i, 0, N - 2) {
		rep(j, 0, M - 2) {			
			for (auto const& vv : position) {
				int s = 0;
				s += board[i + vv[0].X][j + vv[0].Y];
				s += board[i + vv[1].X][j + vv[1].Y];
				s += board[i + vv[2].X][j + vv[2].Y];
				s += board[i + vv[3].X][j + vv[3].Y];
				if (tot < s) tot = s;
			}
		}
	}
	pf1(tot);
}
