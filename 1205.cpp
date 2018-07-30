#include <bits/stdc++.h>
using namespace std;
#define X first
#define Y second
typedef long long ll;
int N, score, P;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> N >> score >> P;
	vector<int> L(N);
	for (int i = 0; i < N; i++) {
		cin >> L[i];
		L[i] = -L[i];
	}
	if (N == 0) {
		cout << 1;
		return 0;
	}
	int num = lower_bound(L.begin(), L.end(), -score)-L.begin();
	if (-score == L.back() && N == P)
		cout << -1;
	else
		cout << (num + 1 > P ? -1 : num + 1);
}
