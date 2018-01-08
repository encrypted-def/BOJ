#include <stdio.h>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
vector<int> before[503]; // before[i] : i를 짓기 위해 이미 지어져있어야할 건물들
vector<int> after[503]; // after[i] : i가 지어져야 지을 수 있는 건물들
int indegree[503];
int time[503]; // 그 건물 하나를 짓는데 드는 시간
int D[503]; // 하위건물까지 고려했을 떄 드는 시간
int main(void) {
	int N;
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		scanf("%d", &time[i]);
		while(true){
			int a;
			scanf("%d", &a);
			if (a == -1)
				break;
			before[i].push_back(a);
			after[a].push_back(i);
			indegree[i]++;
		}
	}
	queue<int> Q;
	for (int i = 1; i <= N; i++) {
		if (indegree[i] == 0)
			Q.push(i);
	} // indegree가 없는 건물들(=하위테크가 필요없는 건물들)을 큐에 삽입
	while (!Q.empty()) {
		int cur = Q.front();
		Q.pop();
		int mx_Subbuilding = 0; // 하위 건물들중에서 가장 오래 걸리는 건물을 짓는데 필요한 시간
		for (auto near : before[cur])
			mx_Subbuilding = max(mx_Subbuilding, D[near]);
		D[cur] = mx_Subbuilding + time[cur];
		for (auto near : after[cur]) {
			indegree[near]--; // 내가 지어져야 지을 수 있는 건물들의 indegree를 1 감소
			if (indegree[near] == 0)
				Q.push(near);
		}
	}
	for(int i = 1; i <= N; i++)
		printf("%d\n", D[i]);

}
