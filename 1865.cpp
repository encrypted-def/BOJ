#include <stdio.h>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
int edge[503][503];
int dist1[503]; // 1번 지점으로부터 떨어진 거리
const int MAX = 1e9;
typedef pair<int, int> PAIR;
#define X first
#define Y second
int main(void) {
	int T;
	scanf("%d", &T);
	while (T--) {
		int N, M, W;
		scanf("%d %d %d", &N, &M, &W);
		for (int i = 1; i <= N; i++) {
			dist1[i] = MAX; // dist1 initialization
			for (int j = 1; j <= N; j++)
				edge[i][j] = MAX; // edge initialization
		}
		dist1[1] = 0;
		while (M--) {
			int S, E, T;
			scanf("%d %d %d", &S, &E, &T);
			edge[S][E] = min(edge[S][E], T);
			edge[E][S] = min(edge[E][S], T);
		}

		while (W--) {
			int S, E, T;
			scanf("%d %d %d", &S, &E, &T);
			edge[S][E] = min(edge[S][E], -T);
		}
		vector<PAIR> adj[503]; // {index, dist}
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				if (edge[i][j] < MAX)
					adj[i].push_back({ j, edge[i][j] });
			}
		}
		bool negCycle = false;
		for (int edge_num = 1; edge_num <= N; edge_num++) {
			for (int st = 1; st <= N; st++) {
				if (dist1[st] == MAX)
					continue;
				for (auto near : adj[st]) {
					if (dist1[st] + near.Y < dist1[near.X]) {
						dist1[near.X] = dist1[st] + near.Y;
						if (edge_num == N) // negative cycle이 존재
							negCycle = true;
					}
				}
			}
		}
		if (dist1[1] < 0 || negCycle)
			printf("YES\n");
		else
			printf("NO\n");		
	}
}
