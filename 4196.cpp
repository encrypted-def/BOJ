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

const int MX = 100004;
int V, E;
vi adj[MX];
vi adj_DAG[MX];
int id[MX], inDegree[MX], outDegree[MX];
vi groupID(MX, -1);
si S;
int curID = 0;
int sccidx = 0;
vector< vi > sccGroup;

int SCC_traverse(int cur) {
	id[cur] = ++curID;
	S.push(cur);
	int link = id[cur];
	for (auto next : adj[cur]) {
		if (id[next] == 0)
			link = min(link, SCC_traverse(next));
		else if (groupID[next] == -1)
			link = min(link, id[next]);
	}
	if (link == id[cur]) {
		sccGroup.pb(vector<int>());
		while (true) {
			int elem = S.top();
			S.pop();
			groupID[elem] = sccidx;
			sccGroup[sccidx].pb(elem);
			if (elem == cur) break;
		}
		sccidx++;
	}
	return link;
}
void SCC_componentDAG() {
	rep(i, 1, V + 1) {
		for (auto next : adj[i]) {
			if (groupID[i] == groupID[next]) continue;
			adj_DAG[groupID[i]].pb(groupID[next]);
		}
	}
	rep(i, 0, sccidx) {
		sort(all(adj_DAG[i]));
		adj_DAG[i].erase(unique(all(adj_DAG[i])), adj_DAG[i].end());
	}
	rep(i, 0, sccidx) {
		for (auto next : adj_DAG[i]) {
			inDegree[next]++;
			outDegree[i]++;
		}
	}
}
void SCC() {
	rep(v, 1, V + 1) {
		if (!id[v])
			SCC_traverse(v);
	}
}
int main(void) {
	int T;
	sf1(T);
	while (T--) {
		sf2(V, E);
		rep(i, 1, V + 1)
			adj[i].clear();
		fill(id + 1, id + V + 1, 0);
		fill(groupID.begin(), groupID.begin() + V + 1, -1);
		sccidx = 0;
		curID = 0;
		while (!S.empty()) S.pop();
		sccGroup.clear();
		while (E--) {
			int a, b;
			sf2(a, b);
			adj[a].pb(b);
		}
		SCC();
		rep(i, 0, sccidx)
			adj_DAG[i].clear();
		fill(inDegree, inDegree + sccidx, 0);
		fill(outDegree, outDegree + sccidx, 0);

		SCC_componentDAG();
		int cnt = 0;
		rep(i, 0, sccidx) {
			if (inDegree[i] == 0) cnt++;
		}
		pf1l(cnt);

	}
}
