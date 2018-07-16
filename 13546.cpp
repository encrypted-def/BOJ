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

int N, K, M;
vi A, ans;
vector<ti3> query;
int cnt[100001];
int bucket[400];
int SZ;
list<int> occur[100001];
bool cmp(ti3 a, ti3 b) {
	if (get<0>(a) / SZ != get<0>(b) / SZ)
		return get<0>(a) / SZ < get<0>(b) / SZ;
	return get<1>(a) < get<1>(b);
}
void mo_add(int x) {
	if (sz(occur[A[x]]) >= 2) {
		cnt[(occur[A[x]].back() - occur[A[x]].front())]--;
		bucket[(occur[A[x]].back() - occur[A[x]].front()) / SZ]--;
	}
	if (occur[A[x]].empty() || occur[A[x]].back() < x)
		occur[A[x]].push_back(x);
	else
		occur[A[x]].push_front(x);
	if (sz(occur[A[x]]) >= 2) {
		cnt[(occur[A[x]].back() - occur[A[x]].front())]++;
		bucket[(occur[A[x]].back() - occur[A[x]].front()) / SZ]++;
	}
}
void mo_erase(int x) {
	if (sz(occur[A[x]]) >= 2) {
		cnt[(occur[A[x]].back() - occur[A[x]].front())]--;
		bucket[(occur[A[x]].back() - occur[A[x]].front()) / SZ]--;
	}
	if (occur[A[x]].back() == x)
		occur[A[x]].pop_back();
	else
		occur[A[x]].pop_front();
	if (sz(occur[A[x]]) >= 2) {
		cnt[(occur[A[x]].back() - occur[A[x]].front())]++;
		bucket[(occur[A[x]].back() - occur[A[x]].front()) / SZ]++;
	}
}
int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0);
	sf2(N, K);
	A.resize(N + 1);
	rep(i, 1, N + 1) sf1(A[i]);
	sf1(M);
	ans.resize(M);
	query.resize(M);
	rep(i, 0, M) {
		int l, r;
		sf2(l, r);
		query[i] = { l,r,i };
	}
	SZ = sqrt(N);
	int range_st = 1;
	int range_en = 1;
	mo_add(1);
	cnt[0] = bucket[0] = K + 3;
	sort(all(query), cmp);
	for (auto& q : query) {
		int l, r, idx;
		tie(l, r, idx) = q;
		while (range_st > l)
			mo_add(--range_st);
		while (range_en < r)
			mo_add(++range_en);
		while (range_st < l)
			mo_erase(range_st++);
		while (range_en > r)
			mo_erase(range_en--);
		int j = (N + 1) / SZ;
		while (bucket[j] == 0) j--;
		int val = min((j + 1) * SZ, N);
		while (cnt[val] == 0) val--;
		ans[idx] = val;
	}
	rep(i, 0, M) pf1l(ans[i]);
}
