void dinic_bfs(vi& level, vector<vi >& C, vector<vi >& F, vector< vi >& adj, int N, int source, int sink) {
	fill(all(level), -1);
	level[source] = 0;
	qi Q;
	Q.push(source);
	while (!Q.empty()) {
		int cur = Q.front();
		Q.pop();
		for (auto next : adj[cur]) {
			if (level[next] == -1 && C[cur][next] > F[cur][next]) {
				level[next] = level[cur] + 1;
				Q.push(next);
			}
		}
	}
}
int dinic_dfs(int cur, int flow, vi& level, vector<vi >& C, vector<vi >& F, vector< vi >& adj, int N, int sink) {
	if (cur == sink) return flow;
	for (auto next : adj[cur]) {
		if (level[next] == level[cur] + 1 && C[cur][next] > F[cur][next]) {
			int cur_flow = dinic_dfs(next, min(C[cur][next] - F[cur][next],flow), level,C,F,adj,N,sink);
			if (cur_flow > 0) {
				F[cur][next] += cur_flow;
				F[next][cur] -= cur_flow;
				return cur_flow;
			}
		}
	}
	return 0;
}
int NetworkFlow(vector<vi >& C, vector<vi >& F, vector< vi >& adj, int N, int source, int sink) {
	int ret = 0;
	vi level(N);
	while (true) {
		dinic_bfs(level, C, F, adj, N, source, sink);
		if (level[sink] == -1) break; // sink에 닿을 수 없을 경우
		while (true) {
			int flow = dinic_dfs(source, 0x7f7f7f7f, level, C, F, adj, N, sink);
			if (flow == 0) break;
			ret += flow;
		}
	}
	return ret;
}
int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int N, M;
	sf2(N, M);
	vector< vi > C(N+M+2);
	vector< vi > F(N + M + 2);
	vector< vi > adj(N + M + 2);
	rep(i, 0, N + M + 2) {
		C[i].resize(N + M + 2);
		F[i].resize(N + M + 2);
	}
	int source = 0;
	int sink = N + M + 1;
	rep(i, 1, N + 1) {
		C[source][i] = 1;
		adj[source].pb(i);
		adj[i].pb(source);
	}
	rep(i, N + 1, N+M + 1) {
		C[i][sink] = 1;
		adj[i].pb(sink);
		adj[sink].pb(i);
	}
	rep(i, 1, N+1) {
		int cnt;
		sf1(cnt);
		while (cnt--) {
			int a;
			sf1(a);
			C[i][N + a] = 1;
			adj[i].pb(N + a);
			adj[N + a].pb(i);
		}
	}
	pf1(NetworkFlow(C, F, adj, N + M + 2, source, sink));
}
