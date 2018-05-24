# pragma GCC optimize ("O3")
# pragma GCC optimize ("Ofast")
# pragma GCC optimize ("unroll-loops")
#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <functional>
#include <iostream>
#include <tuple>
#include <string>
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
ll EXGCD(ll a, ll b, ll&x, ll&y) {
	if (!b)return x = 1, y = 0, a;
	ll d = EXGCD(b, a%b, x, y), t = x;
	return x = y, y = t - a / b * y, d;
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
int N;
int board[22][22];
int ans = 0;
int board_tot = 0;
void calc(int currentDepth, int maxDepth, int dir) {
	if (2 * ans > board_tot) return;
	if (currentDepth == maxDepth) return;
	int board_bak[22][22];
	int comp_num_bak = 0;
	rep(i, 0, N) {
		rep(j, 0, N) {
			board_bak[i][j] = board[i][j];
			if (board_bak[i][j] != 0) comp_num_bak++;
			board[i][j] = 0;
		}
	}
	if (dir == 0) {
		rep(i, 0, N) {
			int ptr2 = -1;
			for (int ptr1 = 0; ptr1 < N; ptr1++) {
				if (board_bak[i][ptr1] == 0) continue;
				if (ptr2 != -1 && board[i][ptr2] == board_bak[i][ptr1]) {
					board[i][ptr2] = 2 * board[i][ptr2];
					ptr2++;
				}
				else {
					if (ptr2 == -1 || board[i][ptr2] != 0)	ptr2++;
					board[i][ptr2] = board_bak[i][ptr1];
				}
			}
		}
	}
	else if (dir == 1) {
		rep(i, 0, N) {
			int ptr2 = N;
			for (int ptr1 = N - 1; ptr1 >= 0; ptr1--) {
				if (board_bak[i][ptr1] == 0) continue;
				if (ptr2 != N && board[i][ptr2] == board_bak[i][ptr1]) {
					board[i][ptr2] = 2 * board[i][ptr2];
					ptr2--;
				}
				else {
					if (ptr2 == N || board[i][ptr2] != 0) ptr2--;
					board[i][ptr2] = board_bak[i][ptr1];
				}
			}
		}
	}
	else if (dir == 2) {
		rep(i, 0, N) {
			int ptr2 = -1;
			for (int ptr1 = 0; ptr1 < N; ptr1++) {
				if (board_bak[ptr1][i] == 0) continue;
				if (ptr2 != -1 && board[ptr2][i] == board_bak[ptr1][i]) {
					board[ptr2][i] = 2 * board[ptr2][i];
					ptr2++;
				}
				else {
					if (ptr2 == -1 || board[ptr2][i] != 0) ptr2++;
					board[ptr2][i] = board_bak[ptr1][i];
				}
			}
		}
	}
	else {
		rep(i, 0, N) {
			int ptr2 = N;
			for (int ptr1 = N - 1; ptr1 >= 0; ptr1--) {
				if (board_bak[ptr1][i] == 0) continue;
				if (ptr2 != N && board[ptr2][i] == board_bak[ptr1][i]) {
					board[ptr2][i] = 2 * board[ptr2][i];
					ptr2--;
				}
				else {
					if (ptr2 == N || board[ptr2][i] != 0) ptr2--;
					board[ptr2][i] = board_bak[ptr1][i];
				}
			}
		}
	}
	int currentMx = 0;
	rep(i, 0, N) rep(j, 0, N) currentMx = max(currentMx, board[i][j]);
	ans = max(currentMx, ans);
	if (currentMx << (maxDepth - currentDepth - 1) <= ans) {
		rep(i, 0, N) rep(j, 0, N) board[i][j] = board_bak[i][j];
		return;
	}
	bool isChanged = false;
	int comp_num = 0;
	rep(i, 0, N) {
		rep(j, 0, N) {
			if (board[i][j] != board_bak[i][j]) isChanged = true;
			if (board[i][j] != 0) comp_num++;
		}
	}
	if (isChanged) {
		if (comp_num_bak == comp_num) {
			rep(nextDir, 0, 4) {
				if (dir == nextDir) continue;
				calc(currentDepth + 1, maxDepth, nextDir);
			}
		}
		else {
			rep(nextDir, 0, 4) {
				calc(currentDepth + 1, maxDepth, nextDir);
			}
		}
	}
	rep(i, 0, N) rep(j, 0, N) board[i][j] = board_bak[i][j];
}
int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0);
	sf1(N);
	rep(i, 0, N) {
		rep(j, 0, N) {
			sf1(board[i][j]);
			board_tot += board[i][j];
		}
	}
	rep(dir, 0, 4) calc(0, 10, dir);
	pf1(ans);

}
