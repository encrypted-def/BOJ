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

class MCMF {
public:
	vector<vector<int> > C, F, D, adj;
	int st, en,N;
	MCMF(int _N, int _st, int _en) {
		N = _N + 2;
		C.resize(N);
		F.resize(N);
		D.resize(N);
		adj.resize(N);
		for (int i = 0; i < N; i++) {
			C[i].resize(N);
			F[i].resize(N);
			D[i].resize(N);
		}
		st = _st;
		en = _en;
	}
	pair<ll, ll> solve() { // return {cost, flow}
		ll c = 0,f=0; // cost,flow
		while (1) {
			vector<int> prev(N, -1);
			vector<int> dist(N, 0x7f7f7f7f);
			dist[st] = 0;
			vector<bool> inQ(N);
			inQ[st] = 1;
			queue<int> Q;
			Q.push(st);
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
			if (prev[en] == -1)break;
			int cf = 0x7f7f7f7f; // current flow
			for (int i = en; i != st; i = prev[i])
				if (cf > C[prev[i]][i] - F[prev[i]][i])
					cf = C[prev[i]][i] - F[prev[i]][i];
			for (int i = en; i != st; i = prev[i]) {
				c += cf * D[prev[i]][i]; // c : cost
				F[prev[i]][i] += cf;
				F[i][prev[i]] -= cf;
			}
			f += cf;
		}
		return { c,f };
	}
	void pushadj(int i, int j, int f, int cost) {
		C[i][j] += f;
		D[i][j] += cost;
		D[j][i] -= cost;
		adj[i].push_back(j);
		adj[j].push_back(i);
	}	
};
int main(void) {
	int T;
	sf1(T);
	while (T--) {
		MCMF mc(24, 0, 23);
		// 1~11 : 선수, 12~22 : Position
		for (int i = 1; i <= 11; i++) {
			mc.pushadj(0, i, 1, 0);
			mc.pushadj(11 + i, 23, 1, 0);
			for (int j = 1; j <= 11; j++) {
				int score;
				sf1(score);
				if(score != 0)
					mc.pushadj(i, 11 + j, 1, -score);
			}
		}
		pf1l(-mc.solve().X);
	}
}
