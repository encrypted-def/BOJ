#include <stdio.h>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
typedef pair<int, int> PAIR;
vector<int> edge[1003];
int isVisited[1003];
int main(void) {
    int N, M;
    scanf("%d %d", &N, &M);
    while (M--) {
        int a, b;
        scanf("%d %d", &a, &b);
        edge[a].push_back(b);
        edge[b].push_back(a);
    }
    int CCcnt = 0;
    for (int i = 1; i <= N; i++) {
        if (isVisited[i])
            continue;
        CCcnt++;
        queue<int> Q;
        isVisited[i] = true;
        Q.push(i);
        while (!Q.empty()) {
            int cur = Q.front();
            Q.pop();
            for (auto const& near : edge[cur]) {
                if (!isVisited[near]) {
                    Q.push(near);
                    isVisited[near] = true;
                }
            }
        }
    }
    printf("%d", CCcnt);
}
