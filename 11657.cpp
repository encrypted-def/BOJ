#include <stdio.h>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
int edge[503][503];
int dist1[503]; // 1번 도시로부터 떨어진 거리
const int MAX = 1e9;
typedef pair<int, int> PAIR;
#define X first
#define Y second
int main(void) {
	int N, M;
	scanf("%d %d", &N, &M);
	for (int i = 1; i <= N; i++) {
		dist1[i] = MAX; // dist1 initialization
		for (int j = 1; j <= N; j++)
			edge[i][j] = MAX; // edge initialization
	}
	dist1[1] = 0;
	while (M--) {
		int A, B, C;
		scanf("%d %d %d", &A, &B, &C);
		edge[A][B] = min(edge[A][B], C);
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
	if (negCycle) {
		printf("-1");
		return 0;
	}
	for (int i = 2; i <= N; i++) {
		if (dist1[i] == MAX)
			dist1[i] = -1;
		printf("%d\n", dist1[i]);
	}

}
