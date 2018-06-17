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

int aho_c2i(char c) {
	return c - 'a';
}
const int MAXN = 150000;
const int MAXC = 26;
void aho_init(const vector<string>& P, vector<vi >& trie, vi& fail, vi& term) {
	rep(i, 0, MAXN) trie[i].resize(MAXC);
	int idx = 0;
	rep(pidx, 0, P.size()) {
		int pos = 0;
		for (auto c : P[pidx]) {
			int c2i = aho_c2i(c);
			if (!trie[pos][c2i]) trie[pos][c2i] = ++idx;
			pos = trie[pos][c2i];
		}
		term[pos] = pidx + 1; // last임을 명시해줌.
	}
	qi Q;
	rep(i, 0, MAXC)
		if (trie[0][i]) Q.push(trie[0][i]);
	while (!Q.empty()) {
		int cur = Q.front();
		Q.pop();
		rep(i, 0, MAXC) {
			if (trie[cur][i]) {
				int p = fail[cur];
				while (p && !trie[p][i]) p = fail[p];
				p = trie[p][i];
				fail[trie[cur][i]] = p;
				if (term[p]) term[trie[cur][i]] = 1;
				Q.push(trie[cur][i]);
			}
		}
	}
}
//"abcbab", ("cb", "cbab") -> return 0 0 0 1 0 2
void ahocorasick(const vector<string>& S, const vector<string>& P) {
	vector<vi > trie(MAXN);
	vi fail(MAXN);
	vi term(MAXN);
	aho_init(P, trie, fail, term);	
	for(auto& s: S) {
		int p = 0;
		bool isYes = false;
		rep(i, 0, s.size()) {
			int c2i = aho_c2i(s[i]);
			while (p && !trie[p][c2i]) p = fail[p];
			p = trie[p][c2i];
			if (term[p]) {
				isYes = true;
				break;
			}
		}
		if (isYes) pf1l("YES");
		else pf1l("NO");
	}
}

int main(void) {
	int N;
	sf1(N);
	vector<string> P(N);
	rep(i, 0, N) sf1(P[i]);
	int M;
	sf1(M);
	vector<string> S(M);
	rep(i, 0, M) sf1(S[i]);
	ahocorasick(S, P);
}
