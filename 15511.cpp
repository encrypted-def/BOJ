#include <stdio.h>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
int n, m;
typedef pair<int, int> PAIR;
#define X first
#define Y second
vector<int> adj[1000005];
int p[1000005];
int main(void) {
	scanf("%d %d", &n, &m);
	while (m--) {
		int a, b;
		scanf("%d %d", &a, &b);
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	for (int st = 1; st <= n; st++) {
		if (p[st] == 0)
			p[st] = 1;
		queue<PAIR> Q;
		Q.push({ st, p[st] });
		while (!Q.empty()) {
			PAIR cur = Q.front();
			Q.pop();
			for (int near : adj[cur.X]) {
				if (p[near] == cur.Y) {
					printf("IMPOSSIBLE");
					return 0;
				}
				else if (p[near] == 0) {
					p[near] = -cur.Y;
					Q.push({ near, p[near] });
				}				
			}
		}
	}
	printf("POSSIBLE");
}
