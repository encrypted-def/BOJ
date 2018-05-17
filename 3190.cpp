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
#include <bitset>
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
int MOD = 1000000000;
ll POW(ll a, ll b, ll MMM = MOD) { ll ret = 1; for (; b; b >>= 1, a = (a*a) % MMM)if (b & 1)ret = (ret*a) % MMM; return ret; }
ll GCD(ll a, ll b) { return b ? GCD(b, a%b) : a; }
ll LCM(ll a, ll b) { if (a == 0 || b == 0)return a + b; return a * (b / GCD(a, b)); }
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
int N, K, L;
int board[105][105];
queue<pii> Q;
int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0);
	sf1(N);
	sf1(K);
	while (K--) {
		int a, b;
		sf2(a, b); a--; b--;
		board[a][b] = 1;
	}
	int ans = 0;
	sf1(L);
	int curX = 0;
	int curY = 0;
	Q.push({ 0,0 });
	board[0][0] = 2;
	int dir = 2; // 0  : down 1 : up 2 : right 3 : left, (0,0)이 좌상단 
	int time = 0;
	while (L--) {
		int x;
		char c;
		sf2(x, c);
		while (time < x) {
			curX = curX + dx[dir];
			curY = curY + dy[dir];
			if (OOB(curX, curY, N, N) || board[curX][curY] == 2) {
				pf1(time+1);
				return 0;
			}
			Q.push({ curX,curY });
			if (board[curX][curY] == 0) {
				board[curX][curY] = 2;
				pii del = Q.front();
				Q.pop();
				board[del.X][del.Y] = 0;
			}
			else // 사과가 있었다면
				board[curX][curY] = 2;			
			time++;
		}
		int Ltable[4] = { 2,3,1,0 };
		int Rtable[4] = { 3,2,0,1 };
		if (c == 'L') dir = Ltable[dir];
		else dir = Rtable[dir];
		
	}
	while (true) {
		curX = curX + dx[dir];
		curY = curY + dy[dir];
		if (OOB(curX, curY, N, N) || board[curX][curY] == 2) {
			pf1(time+1);
			return 0;
		}
		if (board[curX][curY] == 0) {
			board[curX][curY] = 2;
			Q.push({ curX,curY });
			pii del = Q.front();
			Q.pop();
			board[del.X][del.Y] = 0;
		}
		else // 사과가 있었다면
			board[curX][curY] = 2;
		time++;
	}
	return 0;

}
