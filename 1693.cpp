#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
#define X first
#define Y second
typedef pair<int, int> PAIR;
vector<int> adj[100004];
vector<int> child[100004];
const int MAX_COLOR = 20;
bool isVisited[100004];
int n;
int D[100004][MAX_COLOR + 1]; // D[i][color] : 나의 부모의 색깔이 color일 때 i번째 node를 root로 하는 subtree의 최솟값. color = 0이면 부모가 없는 경우를 의미
void fill_table(int root) { // D[root][0~17]을 채우는 함수. 만약 자식 중에 fill_table() 함수를 수행하지 않은 것이 있다면 자식 먼저 fill_table()을 수행하도록 함
	for (auto c : adj[root]) {
		if (isVisited[c])
			continue;
		isVisited[c] = true;
		child[root].push_back(c);
		fill_table(c);
	}
	PAIR min1 = { 0x7ffff000, 100 }; // 최솟값, root의 색깔
	PAIR min2 = { 0x7fffffff, 100 };
	for (int i = 1; i <= MAX_COLOR; i++) { // root의 색깔이 i일 때 subtree의 cost의 합
		int cost = i;
		for (auto c : child[root])
			cost += D[c][i];
		if (make_pair(cost, i) < min1) {
			min2 = min1;
			min1 = { cost, i };
		}
		else if (make_pair(cost, i) < min2)
			min2 = { cost, i };
	}
	for (int i = 0; i <= MAX_COLOR; i++)
		D[root][i] = min1.X;
	D[root][min1.Y] = min2.X; // root의 parent의 색깔이 min1.Y일 경우 min1.X대신 min2.X를 써야함
}
int main(void) {
	scanf("%d", &n);
	for (int i = 0; i < n - 1; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	isVisited[1] = true;
	fill_table(1);
	printf("%d", D[1][0]);
}
