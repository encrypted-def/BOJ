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

const int dx[4] = { 1,-1,0,0 };
const int dy[4] = { 0,0,1,-1 };
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


int segment[2000005];
int lazy[2000005];

void update_lazy(int node, int node_st, int node_en) {
	if ((node_en - node_st + 1) % 2 == 1)
		segment[node] ^= lazy[node];
	if (node_st != node_en) { // leaf가 아닐 경우
		lazy[2 * node] ^= lazy[node];
		lazy[2 * node + 1] ^= lazy[node];
	}
	lazy[node] = 0;
}
// i-j에 val을 더하는 상황
void update_range(int i, int j, int val, int node, int node_st, int node_en) {
	if (lazy[node] != 0)
		update_lazy(node, node_st, node_en);
	if (j < node_st || i > node_en) // i-j, node_st-node_en 범위가 안겹칠경우
		return;
	if (i <= node_st && node_en <= j) { // i-j 범위 안에 node_st-node_en 범위가 완전히 포함될 경우
		lazy[node] = val;
		update_lazy(node, node_st, node_en);
		return;
	}
	update_range(i, j, val, 2 * node, node_st, (node_st + node_en) / 2);
	update_range(i, j, val, 2 * node + 1, (node_st + node_en) / 2 + 1, node_en);
	segment[node] = segment[node * 2] ^ segment[node * 2 + 1];
}

int query(int i, int j, int node, int node_st, int node_en) {
	if (lazy[node] != 0)
		update_lazy(node, node_st, node_en);
	if (node_en < i || j < node_st) // i~j와 node_st~node_en 범위가 아예 겹치지 않는 경우
		return 0;
	if (i <= node_st && node_en <= j) // node_st~node_en 범위가 i~j 범위 안에 완벽하게 들어가는 경우
		return segment[node];
	int mid = (node_st + node_en) / 2;
	return query(i, j, node * 2, node_st, mid) ^ query(i, j, node * 2 + 1, mid + 1, node_en);
}

int N, M;
int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0);
	sf1(N);
	for (int i = 1; i <= N; i++) {
		int num;
		sf1(num);
		update_range(i, i, num, 1, 1, N);
	}
	sf1(M);
	while (M--) {
		int t;
		sf1(t);
		if (t == 1) {
			int a, b, c;
			sf3(a, b, c);
			a++; b++;
			if (a > b)swap(a, b);
			update_range(a, b, c, 1, 1, N);
		}
		else {
			int a, b;
			sf2(a, b);
			a++; b++;
			if (a > b)swap(a, b);
			pf1l(query(a, b, 1, 1, N));
		}
	}
}
