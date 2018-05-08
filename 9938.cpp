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
bool OOB(int x, int y, int N, int M) { return 0 > x || x >= N || 0 > y || y >= M; }
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
#define pf2(a,b) cout << a << ' ' << b << ' '
#define pf3(a,b,c) cout << a << ' ' << b << ' '<< c << ' '
#define pf4(a,b,c,d) cout << a << ' ' << b << ' '<< c << ' '<< d << ' '
#define pf5(a,b,c,d,e) cout << a << ' ' << b << ' '<< c << ' '<< d << ' '<< e << ' '
#define pf6(a,b,c,d,e,f) cout << a << ' ' << b << ' '<< c << ' '<< d << ' '<< e << ' ' << f << ' '
#define pf1l(a) cout << a << '\n'
#define pf2l(a,b) cout << a << ' ' << b << '\n'
#define pf3l(a,b,c) cout << a << ' ' << b << ' '<< c << '\n'
#define pf4l(a,b,c,d) cout << a << ' ' << b << ' '<< c << ' '<< d << '\n'
#define pf5l(a,b,c,d,e) cout << a << ' ' << b << ' '<< c << ' '<< d << ' '<< e << '\n'
#define pf6l(a,b,c,d,e,f) cout << a << ' ' << b << ' '<< c << ' '<< d << ' '<< e << ' ' << f << '\n'

int parent[300002];
bool occupy[300002];
int find(int u) {
	if (u == parent[u]) return u;
	return parent[u] = find(parent[u]);
}
void merge(int u, int v) {
	u = find(u);
	v = find(v);
	if (u == v)
		return;
	parent[u] = v;
}
int N, L;
int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0);
	sf2(N, L);
	rep(i, 1, L + 1)
		parent[i] = i;
	rep(i, 1, N + 1) {
		int a, b;
		sf2(a, b);
		if (!occupy[a]) {
			pf1l("LADICA");
			occupy[a] = true;
			merge(a, b);
			continue;
		}
		if (!occupy[b]) {
			pf1l("LADICA");
			occupy[b] = true;
			merge(b, a);
			continue;
		}
		int insert = find(a);
		if (!occupy[insert]) {
			pf1l("LADICA");
			occupy[insert] = true;
			merge(a, b);
			continue;
		}
		insert = find(b);
		if (!occupy[insert]) {
			pf1l("LADICA");
			occupy[insert] = true;
			merge(b, a);
			continue;
		}
		pf1l("SMECE");
	}
}
