#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
int main(void) {
    //freopen("input.txt", "r", stdin);
    int T;
    cin >> T;
    while (T--) {
        int N, K, W;
        cin >> N >> K;
        int t[1001];
        int depth[1001]; // K로부터 떨어져있는 거리. depth[i]가 큰 것부터 지어나가야 함
        for (int i = 1; i <= N; i++)
            depth[i] = -1;
        vector<int> edge[1001]; // edge[a] : a를 짓기 위해 지어져있어야 하는 건물들의 목록
        vector<int> edge2[1001]; // edge2[a] : a가 지어져야 지을 수 있는 건물들의 목록
        int degree[1001]; // degree[a] : a를 짓기 위해 필요로 하는 건물의 수
        bool issorted[1001]; // topological sort가 되었는지 체크
        for (int i = 1; i <= N; i++) {
            degree[i] = 0;
            issorted[i] = false;
        }
        vector<int> tp; // topological sort 결과를 저장
        queue<int> Q_tp; // topological sort를 위해 필요함
        for (int i = 1; i <= N; i++)
            cin >> t[i];
        while (K--) {
            int a, b;
            cin >> a >> b;
            edge[b].push_back(a);
            edge2[a].push_back(b);
            degree[b]++;
        }
 
        for (int i = 1; i <= N; i++) {
            if (degree[i] == 0)
                Q_tp.push(i); // degree가 0인걸 큐에 전부 삽입
        }
        while (!Q_tp.empty()) {
            int current = Q_tp.front(); Q_tp.pop();
            tp.push_back(current);
            for (auto it = edge2[current].begin(); it != edge2[current].end(); it++)
                if (--degree[*it] == 0) Q_tp.push(*it);
        }
        cin >> W;
        queue<int> Q;
        Q.push(W);
        depth[W] = 0;
        while (!Q.empty()) {
            int current = Q.front(); Q.pop();
            for(auto it = edge[current].begin(); it != edge[current].end(); it++){
                if (depth[*it] == -1) { // 이전에 등장한 적이 없다면
                    depth[*it] = depth[current] + 1;
                    Q.push(*it);
                }
            }
        }
        // D를 채워넣는 것이 위상정렬 순서대로 이루어져야 함
        int D[1001];
        for (int i = 1; i <= N; i++)
            D[i] = 0;
        for (auto it = tp.begin(); it != tp.end(); it++) { // depth가 i인 건물들을 traversal
            int tempmax = 0;
            for (auto it2 = edge[*it].begin(); it2 != edge[*it].end(); it2++) // *it의 이전건물들을 traversal
                tempmax = max(tempmax, D[*it2]);
            D[*it] = tempmax + t[*it];
        }
        
        cout << D[W] << endl;
    }
}
