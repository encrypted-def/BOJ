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

int N, M,L;
int A[8001];
int B[8001];
ll D[8001];
ll fact[8001];
ll finv[8001];
ll inv[8001];
const ll MOD = 1e9 + 7;
int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0);
	sf1(L);
	sf1(N);
	rep(i, 0, N) sf1(A[i]);
	sf1(M);
	rep(i, 0, M) sf1(B[i]);
	fact[0] = fact[1] = 1;
	inv[1] = 1;
	finv[0] = finv[1] = 1;
	rep(i, 2, 2*L + 1) {
		fact[i] = (fact[i - 1] * i)%MOD;
		inv[i] = (MOD - (MOD / i)*inv[MOD%i] % MOD) % MOD;
		finv[i] = finv[i - 1] * inv[i] % MOD;
	}
	D[0] = 1;
	D[1] = 1;
	rep(i, 2, 2*L + 1) {
		for (int j = i - 2; j >= 0; j -= 2) {
			ll val = D[j] * D[i - 1 - j] % MOD;
			val = val * fact[i-1] % MOD;
			val = val * finv[j] % MOD;
			val = val * finv[i - 1-j] % MOD;
			D[i] = (D[i] + val) % MOD;
		}
	}
	ll ans = 0;
	int aidx = 0;
	int bidx = 0;
	int atot = 0;
	int btot = 0;
	vector<int> chunk;
	int cnt = 0;
	while (atot < L || btot < L) {
		if (atot < btot) {
			atot += A[aidx++];
			cnt++;
		}
		else if (atot > btot) {
			btot += B[bidx++];
			cnt++;
		}
		else {
			atot += A[aidx++];
			btot += B[bidx++];
			cnt += 2;
		}
		if (atot == btot) {
			if (cnt > 2)
				chunk.pb(cnt - 2);
			cnt = 0;
		}
	}
	ll ret = 1;
	ll chunklen = 0;
	for (auto c : chunk) {
		ret = ret * finv[c] % MOD;
		ret = ret * D[c] % MOD;
		chunklen += c;
	}
	ret = ret * fact[chunklen] % MOD;
	pf2l(chunklen,ret);
}
