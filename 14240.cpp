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
	if (m == 1)   return 0;
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
////////////////////////////////////////////////////////
//// 1. 위로 볼록인 상황에 대한 코드////////////////////////
//// 2. a*b 범위에 따라 실수연산 or long long 선택//////////
//// 3. x가 증가하는 순서인지를 생성자에 넣어서 알려줌 ////////
////////////////////////////////////////////////////////
class CHT {
public:
	bool isInc;
	CHT(bool _isInc) {
		isInc = _isInc;
	}
	deque<pll> line; // slope, y-intersect
	double inter(int i, int j) { // 직선 line[i], line[j]의 교점의 x좌표
		return 1.00*(line[i].Y - line[j].Y) / (line[j].X - line[i].X);
	}
	ll funcval(ll i, ll x) {
		return line[i].X*x + line[i].Y;
	}
	void pushline(ll a, ll b) {
		line.pb({ a,b });
		int i = sz(line) - 1;
		while (i > 1 && inter(i,i-1) < inter(i-1,i-2)) { // double
	//while (i > 1 && (line[i].Y - line[i - 1].Y)*(line[i - 2].X - line[i - 1].X) < (line[i - 1].Y - line[i - 2].Y)*(line[i - 1].X - line[i].X)) { // ll
			line[i - 1] = line.back();
			line.pop_back();
			i--;
		}

	}
	int binsearch(ll k) { // 점 k가 올라타는 직선의 index
		int st = 0;
		int en = sz(line)-1;
		while (st < en) {
			int mid = (st + en) / 2;
			if (k < inter(mid,mid+1)) en = mid; // double
		//if (k*(line[mid].X-line[mid+1].X) < (line[mid+1].Y-line[mid].Y)) st = mid + 1; // ll
			else st = mid + 1;
		}
		return en;
	}
	ll findval(ll k) {
		if (isInc) {
			if (line.empty()) return INF_LL; // 정상적이라면 발생하지 않을 상황		
			while (sz(line) > 1 && funcval(0, k) > funcval(1, k)) {
				line.pop_front();
			}
			return funcval(0, k);
		}
		if (line.empty()) return INF_LL; // 정상적이라면 발생하지 않을 상황
		if (sz(line) == 1) return funcval(0, k);
		return funcval(binsearch(k), k);
	}
};

int N;
int S[200004];
ll A[200004], B[200004];
// A[i] = sum(S[:i+1])
// B[i] = sum(A[:i+1])
int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0);
	sf1(N);
	rep(i, 1, N+1) {
		sf1(S[i]);
		S[i] = -S[i]; // class 수정하기 귀찮아서 그냥 원소의 부호를 바꿈
		A[i] = A[i - 1] + S[i];
		B[i] = B[i - 1] + A[i];
	}
	ll ans = min(0,S[1]);
	CHT cht(false);
	cht.pushline(-1, 0);
	rep(i, 2, N + 1) {
		ll val = cht.findval(A[i]) + A[i] * (i + 1) - B[i - 1];
		if (ans > S[i]) ans = S[i];
		if (ans > val) ans = val;
		cht.pushline(-i, B[i - 2]);
	}
	pf1l(-ans);
}
