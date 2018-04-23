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
int N;
int S, E;
// Source : 0, row : 1~N, col : N+1~2N, Sink : 2N+1
int f[1003][1003]; // flow
int c[1003][1003]; // capacity
vector<int> adj[1003];
int tot_flow;
void EK_flow() {
	while (true) {
		vector<int> prev(2 * N + 2, -1);
		queue<int> Q;
		Q.push(S);
		while (!Q.empty() && prev[E] == -1) {
			int cur = Q.front();
			Q.pop();
			for (auto next : adj[cur]) {
				if (c[cur][next] > f[cur][next] && prev[next] == -1) {
					Q.push(next);
					prev[next] = cur;
				}
			}
		}
		if (prev[E] == -1)
			return;
		int flow = 1;
		for (int i = E; i != S; i = prev[i]) {
			f[prev[i]][i] += flow;
			f[i][prev[i]] -= flow;
		}
		tot_flow += flow;
	}
}
int main(void) {
	scanf("%d", &N);
	S = 0;
	E = 2 * N + 1;
	int chk1 = 0;
	int chk2 = 0;
	for (int i = 1; i <= N; i++) {
		scanf("%d", &c[S][i]);
		chk1 += c[S][i];
		adj[i].push_back(S);
		adj[S].push_back(i);
	}
	for (int i = N + 1; i <= 2 * N; i++) {
		scanf("%d", &c[i][E]);
		chk2 += c[i][E];
		adj[i].push_back(E);
		adj[E].push_back(i);
	}
	if (chk1 != chk2) {
		printf("-1");
		return 0;
	}
	for (int i = 1; i <= N; i++) {
		for (int j = N + 1; j <= 2 * N; j++) {
			adj[i].push_back(j);
			adj[j].push_back(i);
			c[i][j] = 1;
		}
	}
	EK_flow();
	if (tot_flow != chk1) {
		printf("-1");
		return 0;
	}
	printf("1\n");
	for (int i = 1; i <= N; i++) {
		for (int j = N + 1; j <= 2 * N; j++)
			printf("%d", f[i][j]);
		printf("\n");
	}
	return 0;
}
