#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <functional>
#include <iostream>
#include <tuple>
#include <string>
#pragma warning(disable:4996)
#pragma comment(linker, "/STACK:336777216")
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef tuple<int, int, int> ti3;
typedef tuple<int, int, int, int> ti4;
int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };
int ddx[8] = { 0,0,1,1,1,-1,-1,-1 }, ddy[8] = { 1,-1,1,0,-1,1,0,-1 };
ll MOD = 1000000000;
ll POW(ll a, ll b, ll MMM = MOD) { ll ret = 1; for (; b; b >>= 1, a = (a*a) % MMM)if (b & 1)ret = (ret*a) % MMM; return ret; }
ll gcd(ll a, ll b) { return b ? gcd(b, a%b) : a; }
ll lcm(ll a, ll b) { if (a == 0 || b == 0)return a + b; return a*(b / gcd(a, b)); }
bool OOB(int x, int y, int N, int M) { return 0 > x || x >= N || 0 > y || y >= M; }
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
#define pf1(a) cout << a << ' '
#define pf2(a,b) cout << a << ' ' << b << ' '
#define pf3(a,b,c) cout << a << ' ' << b << ' '<< c << ' '
#define pf4(a,b,c,d) cout << a << ' ' << b << ' '<< c << ' '<< d << ' '
#define pf5(a,b,c,d,e) cout << a << ' ' << b << ' '<< c << ' '<< d << ' '<< e << ' '
#define pf6(a,b,c,d,e,f) cout << a << ' ' << b << ' '<< c << ' '<< d << ' '<< e << ' ' << f << ' '
#define pf1l(a) cout << a << '\n'
#define pf2l(a,b) cout << a << ' ' << b << '\n'
#define pf3l(a,b,c) cout << a << ' ' << b << ' '<< c << '\n'
#define pf4l(a,b,c,d) cout << a << ' ' << b << ' '<< c << ' '<< d << '\n'
#define pf5l(a,b,c,d,e) cout << a << ' ' << b << ' '<< c << ' '<< d << ' '<< e << '\n'
#define pf6l(a,b,c,d,e,f) cout << a << ' ' << b << ' '<< c << ' '<< d << ' '<< e << ' ' << f << '\n'

const int MX = 200003;
string S;
int N;
int sa[MX], pos[MX], lcp[MX];
ti3 node[MX], tmp[MX]; // 앞 d글자의 value / 뒤 d글자의 value / index

void SuffixArray() {

	for (int i = 0; i < N; i++) {
		get<0>(node[i]) = S[i] - 'a';
		get<1>(node[i]) = i != N - 1 ? S[i + 1] - 'a' : -1;
		get<2>(node[i]) = i;
	}
	sort(node, node + N);
	for (int d = 2; d < N; d <<= 1) {
		int M = 0, val = get<0>(node[0]);
		get<0>(node[0]) = pos[get<2>(node[0])] = 0;
		for (int i = 1; i < N; i++) {
			if (val == get<0>(node[i]) && get<1>(node[i - 1]) == get<1>(node[i]))
				get<0>(node[i]) = M;
			else {
				val = get<0>(node[i]);
				get<0>(node[i]) = ++M;
			}
			pos[get<2>(node[i])] = i;
		}
		M++;
		vi cnt(MX + 1, 0);
		for (int i = 0; i < N; i++) {
			int j = get<2>(node[i]) + d;
			get<1>(node[i]) = (j < N ? get<0>(node[pos[j]]) : -1);
			cnt[get<1>(node[i]) + 1]++; // -1 때문에
		}
		for (int i = 1; i < M + 1; i++) cnt[i] += cnt[i - 1];
		for (int i = N - 1; i >= 0; i--)
			tmp[--cnt[get<1>(node[i]) + 1]] = node[i];
		// 뒤 d글자의 value로 정렬 완료
		fill(cnt.begin(), cnt.end(), 0);
		for (int i = 0; i < N; i++) cnt[get<0>(tmp[i])]++;
		for (int i = 1; i < M; i++) cnt[i] += cnt[i - 1];
		for (int i = N - 1; i >= 0; i--)
			node[--cnt[get<0>(tmp[i])]] = tmp[i];
	}
	for (int i = 0; i < N; i++) {
		sa[i] = get<2>(node[i]);
		pos[sa[i]] = i;
	}
}
void LCP() {
	for (int i = 0, k = 0; i < N; i++, k = max(k - 1, 0)) {
		if (pos[i] == N - 1) continue;
		for (int j = sa[pos[i] + 1]; S[i + k] == S[j + k]; k++);
		lcp[pos[i]] = k;
	}
}

int main(void) {
	ios::sync_with_stdio(false);
	sf2(N, S);
	SuffixArray();
	LCP();
	int mx = 0;
	rep(i, 0, N-1) mx = max(mx, lcp[i]);
	pf1(mx);
}
