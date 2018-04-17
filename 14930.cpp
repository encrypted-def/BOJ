#include <stdio.h>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <functional>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };
#define X first
#define Y second
ll N, t;
ll x[100001];
ll v[100001];
int main(void) {
	scanf("%lld %lld", &N, &t);
	int order = 0; // 빨간 구슬이 몇 번째에 위치해있는가.
	vector<ll> fin;
	scanf("%lld %lld", &x[0], &v[0]);
	fin.push_back(x[0] + v[0] * t);
	for (int i = 1; i < N; i++) {
		scanf("%lld %lld", &x[i], &v[i]);
		order += (x[i] < x[0]);
		fin.push_back(x[i] + v[i] * t);
	}
	sort(fin.begin(), fin.end());
	printf("%lld", fin[order]);
}
