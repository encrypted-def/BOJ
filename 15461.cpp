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
ll gcd(ll a, ll b) { return b ? gcd(b, a%b) : a; }
ll lcm(ll a, ll b) { if (a == 0 || b == 0)return a + b; return a * (b / gcd(a, b)); }
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
int N, G;
map<int,int> cowmilk; // a번 소가 cowmilk[a]만큼 생산함
multiset<int> milk; // 모든 소의 milk 값들을 담아둠
ti3 query[100004];
int main(void) {
	set<int> test;
	sf2(N, G);
	rep(i, 0, N) sf3(get<0>(query[i]), get<1>(query[i]), get<2>(query[i]));
	sort(query, query + N);
	int ans = 0;
	rep(i, 0, N + 3) milk.insert(0);
	rep(i, 0, N) {
		int cur_mx = *prev(milk.end());
		int id = get<1>(query[i]);
		int diff = get<2>(query[i]);
		if (cowmilk.find(id) != cowmilk.end()) {
			int id_milk = cowmilk[id];
			milk.erase(milk.find(id_milk));
			int second_mx = *prev(milk.end());
			if (id_milk == cur_mx) {
				if (second_mx == cur_mx) ans++;
				else if (second_mx >= id_milk + diff) ans++;
			}
			else if (id_milk + diff >= cur_mx) ans++;
			milk.insert(id_milk + diff);
			cowmilk[id] = id_milk + diff;
		}
		else { // id번째 cow가 최초 등장
			milk.insert(diff);
			cowmilk[id] = diff;
			if (cur_mx == 0) ans++;
			else if (diff >= cur_mx) ans++;
		}
	}
	pf1(ans);
}
