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
const int MX = 20004;
int V;
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
// x_a : a
// not x_a : N+a
int N, M;
int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0);
	sf2(N, M);
	V = 2 * N;
	rep(i, 0, M) {
		int a, b;
		sf2(a, b);
		// a -> not b
		// -2 -> 2 (N = 5)
		int aidx = a > 0 ? a : -a + N;
		int bidx = b > 0 ? b : -b + N;
		int notaidx = a > 0 ? a + N : -a;
		int notbidx = b > 0 ? b + N : -b;
		adj[notaidx].pb(bidx);
		adj[notbidx].pb(aidx);
	}
	SCC();
	//	rep(i, 1, 2 * N + 1) pf1l(groupID[i]);
	vi state(2*N + 1, -1); // True or false
	rep(i, 1, N + 1) {
		if (groupID[i] == groupID[i + N]) {
			pf1l(0);
			return 0;
		}
//		pf2l(groupID[i], groupID[i + N]);
		state[i] = groupID[i] < groupID[i + N];
	}
	pf1l(1);
	rep(i, 1, N + 1) pf1(state[i]);
	return 0;
}
