#include <stdio.h>
#include <algorithm>
#include <vector>
#define X first
#define Y second
using namespace std;
typedef pair<int, int> PAIR; // idx, dist
int V;
int d = 0; // 트리의 지름
vector<PAIR> edge[100003];
bool isVisited[100003];
int longest_child(int root) { // root의 자식들 중에서 root와 가장 먼 것의 distance
	int mx1 = 0; // 가장 먼 dist
	int mx2 = 0; // 두번째로 먼 dist. d = max(d, mx1+mx2)로 갱신해주기 위해서.
	for (auto child : edge[root]) {
		if (isVisited[child.X]) // 이미 방문한 자식은 제외
			continue;
		isVisited[child.X] = true; // 방문했다고 기록
		int dist = longest_child(child.X) + child.Y; // recursive하게 처리
		if (dist > mx1) {
			mx2 = mx1;
			mx1 = dist;
		}
		else if (dist > mx2) {
			mx2 = dist;
		}
	}
	d = max(d, mx1 + mx2);
	return mx1;
}
int main(void) {
	scanf("%d", &V);
	for (int i = 0; i < V; i++) {
		int v;
		scanf("%d", &v);
		while (true) {
			int a;
			scanf("%d", &a);
			if (a == -1)
				break;
			else {
				int b;
				scanf("%d", &b);
				edge[v].push_back({ a,b });
			}
		}
	}
	isVisited[1] = true;
	longest_child(1);
	printf("%d", d);
}
