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
void dinic_bfs(vi& level, vector<vi >& C, vector<vi >& F, vector< vi >& adj, int N, int source, int sink) {
	fill(all(level), -1);
	level[source] = 0;
	qi Q;
	Q.push(source);
	while (!Q.empty()) {
		int cur = Q.front();
		Q.pop();
		for (auto next : adj[cur]) {
			if (level[next] == -1 && C[cur][next] > F[cur][next]) {
				level[next] = level[cur] + 1;
				Q.push(next);
			}
		}
	}
}
int dinic_dfs(int cur, int flow, vi& level, vector<vi >& C, vector<vi >& F, vector< vi >& adj, int N, int sink) {
	if (cur == sink) return flow;
	for (auto next : adj[cur]) {
		if (level[next] == level[cur] + 1 && C[cur][next] > F[cur][next]) {
			int cur_flow = dinic_dfs(next, min(C[cur][next] - F[cur][next],flow), level,C,F,adj,N,sink);
			if (cur_flow > 0) {
				F[cur][next] += cur_flow;
				F[next][cur] -= cur_flow;
				return cur_flow;
			}
		}
	}
	return 0;
}
int NetworkFlow(vector<vi >& C, vector<vi >& F, vector< vi >& adj, int N, int source, int sink) {
	int ret = 0;
	vi level(N);
	while (true) {
		dinic_bfs(level, C, F, adj, N, source, sink);
		if (level[sink] == -1) break; // sink에 닿을 수 없을 경우
		while (true) {
			int flow = dinic_dfs(source, 0x7f7f7f7f, level, C, F, adj, N, sink);
			if (flow == 0) break;
			ret += flow;
		}
	}
	return ret;
}
int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int N, M, K;
	sf3(N, M, K);
	vector< vi > C(N+M+3);
	vector< vi > F(N + M + 3);
	vector< vi > adj(N + M + 3);
	rep(i, 0, N + M + 3) {
		C[i].resize(N + M + 3);
		F[i].resize(N + M + 3);
	}
	int source = 0;
	int sink = N + M + 1;
	C[source][N + M + 2] = K;
	adj[source].pb(N + M + 2);
	adj[N + M + 2].pb(source);
	rep(i, 1, N + 1) {
		C[N + M + 2][i] = 1;
		adj[N + M + 2].pb(i);
		adj[i].pb(N + M + 2);
		C[source][i] = 1;
		adj[source].pb(i);
		adj[i].pb(source);
	}
	rep(i, N + 1, N+M + 1) {
		C[i][sink] = 1;
		adj[i].pb(sink);
		adj[sink].pb(i);
	}
	rep(i, 1, N+1) {
		int cnt;
		sf1(cnt);
		while (cnt--) {
			int a;
			sf1(a);
			C[i][N + a] = 1;
			adj[i].pb(N + a);
			adj[N + a].pb(i);
		}
	}
	pf1(NetworkFlow(C, F, adj, N + M + 3, source, sink));
}
