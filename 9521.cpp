#include <stdio.h>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;
typedef long long ll;
ll N, K;
ll f[1000004];
const ll MOD = 1000000007ll;
ll D[1000004]; // D[i] : 크기 i의 cycle을 색칠할 수 있는 경우의 수, D[i] = K*(K-1)^(i-1)-D[i-1]
int isVisited_dir[1000004]; // isVisited_dir[i] : i번째 그림에 방문했는지(Directed graph 기준)
int isVisited_undir[1000004]; // isVisited_undir[i] : i번째 그림에 방문했는지(Undirected graph 기준)

vector<int> adj[1000004];
ll div(ll A) {
	if (A%MOD < 0)
		return A%MOD + MOD;
	return A%MOD;
}
int cycleLen(int idx) {
	int cur = idx;
	int len = 1;
	while (f[cur] != idx) {
		cur = f[cur];
		len++;
	}
	return len;
}
ll pow(ll a, ll e) {
	if (e == 0)
		return 1;
	if (e == 1)
		return a % MOD;
	ll t = pow(a, e / 2);
	if (e % 2 == 0)
		return div(t*t);
	else
		return div(div(t*t)*a);
}
int main(void) {
	scanf("%lld %lld", &N, &K);
	for (int i = 1; i <= N; i++) {
		scanf("%lld", &f[i]);
		if (i != f[i]) {
			adj[i].push_back(f[i]);
			adj[f[i]].push_back(i);
		}
	}
	ll ans = 1;
	D[1] = K;
	D[2] = (K*(K - 1)) % MOD;
	ll tmp = D[2];
	for (int i = 3; i <= N; i++) {
		tmp = div(tmp*(K - 1));
		D[i] = div(tmp - D[i - 1]);
	}
	int CycleElemNum = 0;
	for (int i = 1; i <= N; i++) {
		if (isVisited_undir[i])
			continue;
		isVisited_undir[i] = true;
		isVisited_dir[i] = true;
		int cur = i;
		while (!isVisited_dir[f[cur]]) {
			isVisited_dir[cur] = true;
			cur = f[cur];
		}
		// 다음에 들릴 곳(f[cur])이 이미 이전에 방문한 곳. 즉 cur는 cycle에 속함
		int len = cycleLen(cur);
		CycleElemNum += len; // 현재의 component에 있는 cycle의 길이를 구해서 추가함
		ans = div(ans*D[len]); // 전체 경우의 수에 곱해줌
		stack<int> S;
		// weak component의 모든 원소에 대해 isVisited_undir[i]를 true로 만들어줄것임
		S.push(i);
		while (!S.empty()) {
			int cur = S.top();
			S.pop();
			for (auto next : adj[cur]) {
				if (!isVisited_undir[next]) {
					isVisited_undir[next] = true;
					S.push(next);
				}
			}
		}
	}
	printf("%lld", div(ans*pow(K-1, N - CycleElemNum)));
	return 0;
}
