#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long LL;
typedef pair<int, int> PAIR;
const LL MOD = 1000000007LL;
#define X first
#define Y second
LL D[100004]; // D[i] : i를 도착지로 하는 경로의 가중치의 합. 단, i의 subtree에서 i로 가는 경로에 대해서만 생각
bool isVisited[100004];
LL cost = 0;
vector<PAIR> adj[100004]; // <idx, edge cost>
int N;

LL mod(LL a) {
	if (a % MOD < 0)
		return a%MOD + MOD;
	return a%MOD;
}
LL square(LL a) {
	return mod(a*a);
}
void calc(int root) { // D[root]를 계산하고 cost에 root의 subtree간에 이동하는 경로를 추가하는 함수
	LL subtree_sum = 0;
	LL add_cost = 0;
	for (auto c : adj[root]) {
		if (isVisited[c.X])
			continue;
		isVisited[c.X] = true;
		calc(c.X);
		LL elem = mod((D[c.X] + 1)*c.Y);
		subtree_sum = mod(subtree_sum+elem);
		add_cost = mod(add_cost-square(elem));
	}
	// D의 subtree의 cost가 {a, b, c, d}라고 한다면 ab+ac+ad+bc+bd+cd를 cost에 추가해줘야하고 이건 ((a+b+c+d)^2-(a^2+b^2+c^2+d^2))/2으로 쉽게 계산 가능
	add_cost = mod(add_cost + square(subtree_sum));
	if (add_cost % 2 == 0)
		cost = mod(cost + add_cost / 2);
	else
		cost = mod(cost + (add_cost + MOD) / 2);
	D[root] = mod(subtree_sum);
	cost = mod(cost + D[root]);
}
int main(void) {
	scanf("%d", &N);
	for (int i = 0; i < N - 1; i++) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		adj[a].push_back({ b,c });
		adj[b].push_back({ a,c });
	}
	isVisited[1] = true;
	calc(1);
	printf("%lld", cost);
}
