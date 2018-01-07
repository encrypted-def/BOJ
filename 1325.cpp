#include <stdio.h>
#include <stack>
#include <vector>
#include <algorithm>
using namespace std;
typedef pair<int, int> PAIR;
#define X first
#define Y second
int N, M;
vector<int> adj[10004]; // adj[i] : i를 해킹하면 해킹할 수 있는 컴퓨터들
int D[10004]; // D[i] : i를 해킹했을 때 총 몇개의 컴퓨터를 해킹할 수 있는지
int mx = 0;
int main(void) {
	scanf("%d %d", &N, &M);
	while (M--) {
		int a, b;
		scanf("%d %d", &a, &b);
		adj[b].push_back(a);
	}
	for (int st = 1; st <= N; st++) { // st를 해킹할것임 
		bool isVisited[10005] = { 0, };
		isVisited[st] = true;
		stack<int> S;
		S.push(st);
		int cnt = 1;
		while (!S.empty()) {
			int cur = S.top();
			S.pop();
			for (auto near : adj[cur]) {
				if (!isVisited[near]) {
					isVisited[near] = true;
					S.push(near);
					cnt++;
				}
			}
		}
		D[st] = cnt;
		mx = max(mx, cnt);
	}
	for (int i = 1; i <= N; i++) {
		if (D[i] == mx)
			printf("%d ", i);
	}
}
