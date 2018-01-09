#include <stdio.h>
#include <queue>
#include <vector>
#include <algorithm>
#include <tuple>
#include <functional>
using namespace std;
typedef pair<int, int> PAIR;
typedef tuple<int, int, int> TUPLE;
int D[103][10003]; // D[i][j] : 1번 도시에서 i번 도시까지 비용 j를 써서 갈 때 최소 시간
const int INF = 1 << 30;
int main(void) {
	int T;
	scanf("%d", &T);
	while (T--) {
		int N, M, K;
		scanf("%d %d %d", &N, &M, &K);
		for (int i = 1; i <= N; i++)
			for (int j = 1; j <= M; j++)
				D[i][j] = INF;
		D[1][0] = 0;
		vector<TUPLE> adj[103]; // {departure city idx, cost, time}
		while (K--) {
			int u, v, c, d;
			scanf("%d %d %d %d", &u, &v, &c, &d);
			adj[u].push_back({ v, c, d });
		}
		priority_queue<TUPLE, vector<TUPLE>, greater<TUPLE> > PQ; // {time, city idx, cost}
		PQ.push({ 0,1,0 });
		bool ExistsPath = false;
		while(!PQ.empty()) {
			auto cur = PQ.top();
			PQ.pop();
			int time_cur = get<0>(cur);
			int city_cur = get<1>(cur);
			int cost_cur = get<2>(cur);
			if (city_cur == N) {
				printf("%d\n", time_cur); // 주어진 cost 내에서 time이 작은 순으로 보고있기 때문에 N에 도달하는 즉시 출력하면 됨
				ExistsPath = true;
				break;
			}
			if (D[city_cur][cost_cur] < time_cur) // 이미 city에 cost를 써서 더 빨리 도달한 경우가 있을 경우
				continue;
			for (auto near : adj[city_cur]) {
				int city_near = get<0>(near);
				int cost_near = get<1>(near);
				int time_near = get<2>(near);
				if (cost_cur + cost_near > M) // 예산을 초과했을 경우
					continue; 
				if (D[city_near][cost_cur + cost_near] > time_near + time_cur) { // 더 좋은 경로를 찾은 경우
					D[city_near][cost_cur + cost_near] = time_near + time_cur;
					PQ.push({ time_near + time_cur , city_near, cost_cur + cost_near });
				}
			}
		}
		if (!ExistsPath)
			printf("Poor KCM\n");
	}
}
