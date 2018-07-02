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
const int MX_N = 402;
const int MX_M = 402;
const int MX_V = MX_N + MX_M + 2;
vi level(MX_V);
vector< vi > C(MX_V);
vector< vi > F(MX_V);
vector< vi > D(MX_V); // must resize C,F,D
vector< vi > adj(MX_V);
int source, sink;

// return {cost, flow}
pll MCMF() {
	ll tot_flow = 0;
	ll tot_cost = 0;
	while (true) {
		vi prev(MX_V, -1);
		vi dist(MX_V, 0x7f7f7f7f);
		dist[source] = 0;
		vector<bool> inQ(MX_V);
		inQ[source] = true;
		qi Q;
		Q.push(source);
		while (!Q.empty()) {
			int cur = Q.front();
			Q.pop();
			inQ[cur] = false;
			for (auto next : adj[cur]) {
				if (C[cur][next] > F[cur][next] && dist[next] > dist[cur] + D[cur][next]) {
					dist[next] = dist[cur] + D[cur][next];
					prev[next] = cur;
					if (!inQ[next]) {
						Q.push(next);
						inQ[next] = true;
					}
				}
			}
		}
		if (prev[sink] == -1) break;
		int flow = 0x7f7f7f7f;
		for (int i = sink; i != source; i = prev[i])
			if (flow > C[prev[i]][i] - F[prev[i]][i])
				flow = C[prev[i]][i] - F[prev[i]][i];
		for (int i = sink; i != source; i = prev[i]) {
			tot_cost += flow * D[prev[i]][i];
			F[prev[i]][i] += flow;
			F[i][prev[i]] -= flow;
		}
		tot_flow += flow;
	}
	return { tot_cost,tot_flow };
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0);
	sf2(N, M);
	source = 0;
	sink = N + M + 1;
	rep(i, 0, MX_V) {
		C[i].resize(MX_V);
		F[i].resize(MX_V);
		D[i].resize(MX_V);
	}
	rep(i, 1, N + 1) {
		C[source][i] = 1;
		adj[source].pb(i);
		adj[i].pb(source);
	}
	rep(i, N + 1, N + M + 1) {
		C[i][sink] = 1;
		adj[i].pb(sink);
		adj[sink].pb(i);
	}
	rep(i, 1, N + 1) {
		int cnt;
		sf1(cnt);
		while (cnt--) {
			int a, money;
			sf2(a,money);
			money = -money;
			C[i][N + a] = 1;
			adj[i].pb(N + a);
			adj[N + a].pb(i);
			D[i][N + a] = money;
			D[N + a][i] = -money;
		}
	}
	auto ans = MCMF();
	pf1l(ans.Y);
	pf1l(-ans.X);
}
