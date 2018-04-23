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
int N, M;
// 0 : source, 1~N : 지민 팀, N+1~M : 한수 팀, N+M+1 : sink
int f[103][103]; // 현재 흐르는 유량
int c[103][103]; // capacity
vector<int> adj[103];
int tot_flow;
void EK_flow() { // Edmonds-Karp
	int S = 0; // source
	int E = N + M + 1; // sink
	while (true) {
		vector<int> prev(N + M + 2, -1);
		queue<int> Q;
		Q.push(S);
		while (!Q.empty()) {
			int cur = Q.front();
			Q.pop();
			for (int next : adj[cur]) {
				if (c[cur][next] > f[cur][next] && prev[next] == -1) { // 유량을 보낼 수 있고 아직 방문하지 않았을 경우
					Q.push(next);
					prev[next] = cur;
					if (next == E) // sink에 도달시
						break;
				}
			}
		}
		if (prev[E] == -1) // sink에 도달할 수 없을 경우
			return;
		//int flow = 0x7f7f7f7f;
		//for (int i = E; i != S; i = prev[i]) 
		//	flow = min(flow, c[prev[i]][i] - f[prev[i]][i]); 
		// 원래는 경로를 따라가며 flow를 찾아야하나 이 문제의 경우는 1일 수 밖에 없음
		int flow = 1;
		for (int i = E; i != S; i = prev[i]) {
			f[prev[i]][i] += flow;
			f[i][prev[i]] -= flow;
		}
		tot_flow += flow;
	}
}
void flipping(int i, int j) { // i -> j를 없애고 싶은 상황.
	int S = 0; // source
	int E = N + M + 1; // sink
	f[S][i]--;
	f[i][S]++;
	f[i][j]--;
	f[j][i]++;
	f[j][E]--;
	f[E][j]++; // 일단 잠시 경로를 없애놓음
	queue<int> Q;
	Q.push(i);
	vector<int> prev(N + M + 2, -1);
	prev[i] = S;
	while (!Q.empty()) {
		int cur = Q.front();
		Q.pop();
		for (int next : adj[cur]) {
			if (cur == i && next <= j) // 사전순을 위배하면 안됨
				continue;
			if (next <= i) // 사전순을 위배하면 안됨
				continue;
			if (c[cur][next] > f[cur][next] && prev[next] == -1) { // 유량을 보낼 수 있고 아직 방문하지 않았을 경우
				Q.push(next);
				prev[next] = cur;
				if (next == E) // sink에 도달시
					break;
			}
		}
	}
	if (prev[E] == -1) { // sink에 도달할 수 없을 경우
		f[S][i]++;
		f[i][S]--;
		f[i][j]++;
		f[j][i]--;
		f[j][E]++;
		f[E][j]--;
		return; // 다 돌려놓고 return
	}
	int flow = 1;
	for (int i = E; i != S; i = prev[i]) {
		f[prev[i]][i] += flow;
		f[i][prev[i]] -= flow;
	}
}
int main(void) {
	scanf("%d %d", &N, &M);
	int tmp1 = 0, tmp2 = 0;
	for (int i = 1; i <= N; i++) {
		adj[0].push_back(i);
		adj[i].push_back(0);
		scanf("%d", &c[0][i]);
		tmp1 += c[0][i];
	}
	for (int i = N + 1; i <= N+M; i++) {
		adj[i].push_back(N+M + 1);
		adj[N+M + 1].push_back(i);
		scanf("%d", &c[i][N+M + 1]);
		tmp2 += c[i][N+M + 1];
	}
	for (int i = 1; i <= N; i++) {
		for (int j = N + 1; j <= N+M; j++) {
			adj[i].push_back(j);
			adj[j].push_back(i);
			c[i][j] = 1;
		}
	}
	if (tmp1 != tmp2) {
		printf("-1");
		return 0;
	}
	EK_flow();
	if (tot_flow != tmp1) {
		printf("-1");
		return 0;
	}
	for (int i = 1; i <= N; i++) {
		for (int j = N + 1; j <= N+M; j++) {
			if (f[i][j] == 1) // i -> j가 흐르고 있으면 이를 없애보려고 할 것임
				flipping(i, j);
			printf("%d", f[i][j]);
		}
		printf("\n");
	}
}
