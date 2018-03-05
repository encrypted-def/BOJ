#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;
int n, k, m;
bool D[1005];
vector<int> adj[1005];
vector<int> cc;
bool isVisited[1005];
int main(void) {
	scanf("%d %d %d", &n, &m, &k);
	while (m--) {
		int a, b;
		scanf("%d %d", &a, &b);
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	for (int st = 1; st <= n; st++) {
		if (isVisited[st])
			continue;
		int cnt = 0;
		isVisited[st]++;
		queue<int> Q;
		Q.push(st);
		while (!Q.empty()) {
			cnt++;
			int cur = Q.front();
			Q.pop();
			for (int near : adj[cur]) {
				if (isVisited[near])
					continue;
				isVisited[near] = true;
				Q.push(near);
			}
		}
		cc.push_back(cnt);
	}
	D[0] = true;
	for (int num : cc) {
		for (int i = 1000 - num; i >= 0; i--)
			if (D[i] == true) D[i + num] = true;
	}
	if (D[k])
		printf("SAFE");
	else
		printf("DOOMED");
}
