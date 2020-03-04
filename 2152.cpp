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

////////////////////////////////////////////////////////////////////////////////////////////////////
/////////// 1. 1-indexed, Tarjan algorithm /////////////////////////////////////////////////////////
/////////// 2. getSCC를 call해 우선 scc를 만들어낸 후 getDAG를 call해야함 ///////////////////////////////
/////////// 3. i>j일 경우 i번째 scc가 j번째 scc보다 위상정렬 상에서 앞에 존재. 즉 위상정렬의 역순 ////////////
/////////// 4. adj에는 알아서 값을 넣어주어야 함 ///////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
class SCC {
public:
	int N;
	vector<vector<int> > adj, sccadj, comp; // sccadj : i번째 scc에 인접한 scc들, comp : i번째 scc가 담고있는 원소들
	vector<int> id, in, out, group; // in, out : in/out degree of scc, group : i가 어느 scc에 속하는가.
	stack<int> S;
	int m, curID; // m : scc의 갯수(scc의 idx로 dfs에서 쓰임)
	SCC(int _N) {
		N = _N + 5;
		curID = m = 0;
		adj.resize(N);
		id.resize(N);
		group.resize(N, -1);
		N = _N;
	}
	void getSCC() {
		for (int i = 1; i <= N; i++) {
			if (!id[i])
				dfs(i);
		}
	}
	int dfs(int cur) {
		id[cur] = ++curID;
		S.push(cur);
		int link = id[cur];
		for (auto next : adj[cur]) {
			if (id[next] == 0)
				link = min(link, dfs(next));
			else if (group[next] == -1)
				link = min(link, id[next]);
		}
		if (link == id[cur]) {
			comp.push_back(vector<int>());
			while (true) {
				int t = S.top();
				S.pop();
				group[t] = m;
				comp[m].push_back(t);
				if (t == cur) break;
			}
			m++;
		}
		return link;
	}
	void getDAG() {
		sccadj.resize(m);
		in.resize(m);
		out.resize(m);
		for (int i = 1; i <= N; i++) {
			for (auto next : adj[i]) {
				if (group[i] == group[next]) continue;
				sccadj[group[i]].push_back(group[next]);
			}
		}
		for (int i = 0; i < m; i++) {
			sort(sccadj[i].begin(), sccadj[i].end());
			sccadj[i].erase(unique(sccadj[i].begin(), sccadj[i].end()), sccadj[i].end());
		//	for (auto next : sccadj[i]) {
		//		in[next]++;
		//		out[i]++;
		//	}
		}
	}
};


int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int N, M, S, T;
	sf4(N, M, S, T);
	SCC scc(N);
	while (M--) {
		int a, b;
		sf2(a, b);
		scc.adj[a].pb(b);
	}
	scc.getSCC();
	scc.getDAG();
	int st_scc = scc.group[S];
	int en_scc = scc.group[T];
	qi Q;
	vi D(scc.m, 0);
	D[st_scc] = sz(scc.comp[st_scc]);
	for (int i = st_scc; i >= 0; i--) {
		if(D[i]==0) continue;
		for (auto next : scc.sccadj[i])
			D[next] = max(D[next], sz(scc.comp[next]) + D[i]);
	}
	pf1l(D[en_scc]);
}
