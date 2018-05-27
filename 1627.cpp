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
ll MOD = 1000000000;
ll POW(ll a, ll b, ll MMM = MOD) { ll ret = 1; for (; b; b >>= 1, a = (a*a) % MMM)if (b & 1)ret = (ret*a) % MMM; return ret; }
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

int N;
string board;
vi P;
vector<pii> seq;
int G[3005]; // Grundy Number
int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0);
	sf2(N, board);
	//sf1(board);
	//N = board.size();
	if (N == 3) {
		int Pcnt = 0;
		rep(i, 0, N) Pcnt += (board[i] == 'P');
		if (Pcnt % 2 == 1)
			pf1l("LOSING");
		else {
			pf1l("WINNING");
			rep(i, 0, N) {
				if (board[i] != 'P')
					pf1(i + 1);
			}
		}
		return 0;
	}
	rep(i, 0, N-2) {
		assert(!(board[i] == 'P' && board[i + 1] == 'P' && board[i + 2] == 'P'));
	}
	vi ans;
	rep(i, 0, N) {
		if (i >= 2) {
			if (board[i - 2] == 'P' && board[i - 1] == 'P') {
				ans.pb(i+1);
				continue;
			}
		}
		if (i <= N - 3) {
			if (board[i + 1] == 'P' && board[i + 2] == 'P') {
				ans.pb(i + 1);
				continue;
			}
		}
		if (i != 0 && i != N - 1) {
			if (board[i - 1] == 'P' && board[i + 1] == 'P') {
				ans.pb(i + 1);
				continue;
			}
		}
	}
	if (!ans.empty()) {
		pf1l("WINNING");
		pfvec(ans);
		return 0;
	}
	rep(i, 0, N) 
		if (board[i] == 'P') P.pb(i);
	G[0] = 0;
	G[1] = 1;
	G[2] = 1;
	G[3] = 1;
	G[4] = 2;
	G[5] = 2;
	G[6] = 0;
	rep(i, 7, N+1) {
		vector<bool> occur(N+5);
		occur[G[i - 3]] = true;
		occur[G[i - 4]] = true;
		occur[G[i - 5]] = true;
		rep(a, 1, (i - 5) / 2 + 1) {
			if ((G[a] ^ G[i - 5 - a]) <= N + 5) {
				occur[G[a] ^ G[i - 5 - a]] = true;
			}
		}
		int t = 0;
		while (occur[t]) t++;
		G[i] = t;
	}


	int XX = 0;
	if (P.empty()) {
		seq.pb(make_pair(1, N));
		XX ^= G[N];
	}
	else {
		if (P[0] > 2) {
			seq.pb(make_pair(1, P[0] - 2));
			XX ^= G[P[0] - 2];
		}
		rep(i, 1, P.size()) {
			int len = P[i] - P[i - 1] + 1;
			if (len > 6) {
				seq.pb(make_pair(P[i - 1] + 4, len - 6));
				XX ^= G[len - 6];
			}
		}
		if (N - 1 - P[P.size() - 1] > 2) {
			int len = N - 1 - P[P.size() - 1];
			seq.pb(make_pair(P[P.size() - 1] + 4, len - 2));
			XX ^= G[len - 2];
		}
	}
	if (XX == 0) {
		pf1("LOSING");
		return 0;
	}
	else {
		pf1l("WINNING");
		rep(i, 0, seq.size()) {
			if (seq[i].Y == 1) {
				if (XX == 1) pf1(seq[i].X);
				continue;
			}
			if (seq[i].Y == 2) {
				if (XX == 1) pf2(seq[i].X, seq[i].X + 1);
				continue;
			}
			if (seq[i].Y == 3) {
				if (XX == 1) pf3(seq[i].X, seq[i].X+1, seq[i].X+2 );
				continue;
			}
			if (seq[i].Y == 4) {
				if (XX == 1) pf2(seq[i].X, seq[i].X + 3);
				if (XX == 2) pf2(seq[i].X + 1, seq[i].X + 2);
				continue;
			}
			int nXX = XX ^ G[seq[i].Y];
			if (nXX == G[seq[i].Y - 3])	pf1(seq[i].X);
			if (nXX == G[seq[i].Y - 4])pf1(seq[i].X + 1);
			rep(a, 2, seq[i].Y - 2) {
				if (nXX == (G[a - 2] ^ G[seq[i].Y - a - 3])) pf1(seq[i].X + a);
			}
			if (nXX == G[seq[i].Y - 4])pf1(seq[i].X + seq[i].Y-2);
			if (nXX == G[seq[i].Y - 3])	pf1(seq[i].X + seq[i].Y - 1);
		}
	}	
}
