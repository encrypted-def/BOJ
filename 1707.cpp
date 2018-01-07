#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;
vector<int> edge[20001];
int depth[20001];
bool solve() {
    int V, E;
    scanf("%d %d", &V, &E);
    for (int i = 1; i <= V; i++) {
        depth[i] = -1;
        edge[i].clear();
    }
    while (E--) {
        int a, b;
        scanf("%d %d", &a, &b);
        edge[a].push_back(b);
        edge[b].push_back(a);
    }
    queue<int> Q;
    for (int st = 1; st <= V; st++) {
        if (depth[st] != -1) // 이미 방문한 node일 경우
            continue;
        Q.push(st);
        depth[st] = 0;
        while (!Q.empty()) {
            int cur = Q.front();
            Q.pop();
            for (auto const& a : edge[cur]) {
                if (depth[a] != -1) // 이미 방문한 노드일 경우
                    continue;
                depth[a] = depth[cur] + 1;
                Q.push(a);
            }
        }
    }
    for (int v = 1; v <= V; v++) {
        for (auto const& a : edge[v]) {
            if ((depth[v] - depth[a]) % 2 == 0) // 인접한데 같은 그룹에 속해있는 경우
                return false;
        }
    }
    return true;
}
int main(void) {
    int K;
    scanf("%d", &K);
    while (K--) {
        bool tmp = solve();
        if (tmp)
            printf("YES\n");
        else
            printf("NO\n");
    }
}
