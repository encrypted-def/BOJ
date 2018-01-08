#include <stdio.h>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>
using namespace std;
vector<int> after[32003]; // after[i] : 문제 i를 풀고나서 시도해야할 문제들의 목록
int indegree[32003];
int main(void) {
	int N, M;
	scanf("%d%d", &N, &M);
	while (M--) {
		int A, B;
		scanf("%d%d", &A, &B);
		indegree[B]++;
		after[A].push_back(B);
	}
	priority_queue<int, vector<int>, greater<int> > PQ; // Priority Queue를 사용해야 지속적으로 혀내 풀 수 있는 문제들 중에서 가장 쉬운 문제를 고려한다.
	for (int i = 1; i <= N; i++) {
		if (indegree[i] == 0)
			PQ.push(i);
	} // indegree가 없는 건물들(=먼저 풀어야할 문제가 없는 문제들)을 큐에 삽입
	while (!PQ.empty()) {
		int cur = PQ.top();
		PQ.pop();
		printf("%d ", cur);
		for (auto near : after[cur]) {
			indegree[near]--; // 내가 지어져야 지을 수 있는 건물들의 indegree를 1 감소
			if (indegree[near] == 0)
				PQ.push(near);
		}
	}
	return 0;
}
