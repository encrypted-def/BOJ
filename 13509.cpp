#include <bits/stdc++.h>
using namespace std;
#define X first
#define Y second
typedef long long ll;
map<int, int> compCoor;
int dist[200003];
vector<int > seg;
vector<tuple<int, int, int> > V;
int N;
void init() {
	for (int i = N - 1; i > 0; i--)
		seg[i] = max(seg[i << 1], seg[i << 1 ^ 1]);
}
void update(int i, int val) {
	for (seg[i += N] = val; i > 1; i >>= 1) seg[i >> 1] = max(seg[i], seg[i ^ 1]);
}
int query(int l, int r) {
	int mx = -0x3f7f7f7f;
	for (l += N, r += N + 1; l < r; l >>= 1, r >>= 1) {
		if (l & 1) mx = max(mx, seg[l++]);
		if (r & 1) mx = max(mx, seg[--r]);
	}
	return mx;
}
void solve() {
	seg.clear();
	compCoor.clear();
	vector<int> tmp;
	for (int i = 0; i < N; i++)
		tmp.push_back(get<1>(V[i]));
	sort(tmp.begin(), tmp.end());
	tmp.erase(unique(tmp.begin(), tmp.end()), tmp.end());
	int Ysz = tmp.size();
	for (int i = 0; i < Ysz; i++)
		compCoor[tmp[i]] = i;
	sort(V.begin(), V.end());
	for (int i = 0; i < N-1; i++) {
		if (get<0>(V[i]) == get<0>(V[i + 1]) &&  get<1>(V[i])==get<1>(V[i+1]))
			dist[get<2>(V[i])] = dist[get<2>(V[i + 1])] = 0;
	}
	seg.resize(2 * N, -0x3f7f7f7f);
	for (int i = 0; i < N; i++) {
		int x, y, idx;
		tie(x, y, idx) = V[i];
		int ytrans = compCoor[y];
		int val = query(0, ytrans);
		if (x + y - val < dist[idx])
			dist[idx] = x + y - val;
		update(ytrans, x + y);
	}
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> N;
	
	fill(dist, dist + N, 0x3f3f3f3f);
	V.resize(N);
	for (int i = 0; i < N; i++) {
		int x, y;
		cin >> x >> y;
		V[i]={ x,y,i };
	}
	solve();
	for (int i = 0; i < N; i++)
		get<0>(V[i]) = -get<0>(V[i]);
	solve();
	for (int i = 0; i < N; i++)
		get<1>(V[i]) = -get<1>(V[i]);
	solve();
	for (int i = 0; i < N; i++)
		get<0>(V[i]) = -get<0>(V[i]);
	solve();
	for (int i = 0; i < N; i++)
		cout << dist[i] << '\n';

}
