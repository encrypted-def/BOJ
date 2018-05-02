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
#pragma warning(disable:4996)
#pragma comment(linker, "/STACK:336777216")
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef tuple<int, int, int> ti3;
typedef tuple<int, int, int, int> ti4;
int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };
int ddx[8] = { 0,0,1,1,1,-1,-1,-1 }, ddy[8] = { 1,-1,1,0,-1,1,0,-1 };
ll MOD = 1000000000;
ll POW(ll a, ll b, ll MMM = MOD) { ll ret = 1; for (; b; b >>= 1, a = (a*a) % MMM)if (b & 1)ret = (ret*a) % MMM; return ret; }
ll gcd(ll a, ll b) { return b ? gcd(b, a%b) : a; }
ll lcm(ll a, ll b) { if (a == 0 || b == 0)return a + b; return a*(b / gcd(a, b)); }
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
#define pf1(a) cout << a << ' '
#define pf2(a,b) cout << a << ' ' << b
#define pf3(a,b,c) cout << a << ' ' << b << ' '<< c << ' '
#define pf4(a,b,c) cout << a << ' ' << b << ' '<< c << ' '<< d << ' '
#define pf5(a,b,c) cout << a << ' ' << b << ' '<< c << ' '<< d << ' '<< e << ' '
#define pf6(a,b,c) cout << a << ' ' << b << ' '<< c << ' '<< d << ' '<< e << ' ' << f << ' '
#define pf1l(a) cout << a << '\n'
#define pf2l(a,b) cout << a << '\n' << b
#define pf3l(a,b,c) cout << a << '\n' << b << '\n' << c << '\n'
#define pf4l(a,b,c) cout << a << '\n' << b << '\n' << c << '\n' << d << '\n'
#define pf5l(a,b,c) cout << a << '\n' << b << '\n' << c << '\n' << d << '\n' << e << '\n'
#define pf6l(a,b,c) cout << a << '\n' << b << '\n' << c << '\n' << d << '\n' << e << '\n' << f << '\n'


vi truth;
int N, M;
int conn[53][53];

int main(void) {
	ios_base::sync_with_stdio(false);
	sf2(N, M);
	int tmp;
	sf1(tmp);
	rep(i, 0, tmp) {
		int t;
		sf1(t);
		truth.push_back(t);
	}
	vi party[53];
	rep(p, 0, M) {
		int num;
		sf1(num);
		rep(i, 0, num) {
			int t;
			sf1(t);
			party[p].pb(t);
		}
		rep(i, 0, num) {
			rep(j, i + 1, num) {
				conn[party[p][i]][party[p][j]] = true;
				conn[party[p][j]][party[p][i]] = true;
			}
		}
	}
	queue<int> Q;
	vi isVisited(N + 1, 0);
	for (auto t : truth) {
		Q.push(t);
		isVisited[t] = 1;
	}
	while (!Q.empty()) {
		int cur = Q.front();
		Q.pop();
		rep(i, 1, N + 1) {
			if (conn[cur][i]) {
				if (!isVisited[i]) {
					isVisited[i] = 1;
					Q.push(i);
				}
			}
		}
	}
	int cnt = 0;
	rep(i, 0, M) {
		bool isPossible = true;
		for (auto p : party[i]) 
			if (isVisited[p]) isPossible = false;
		cnt += isPossible;
	}
	pf1(cnt);
}
