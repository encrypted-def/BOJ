#include <stdio.h>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
vector<int> edge[101];
#define PAIR pair<int, int>
#define X first
#define Y second
int N, M;
int KBvalue(int i) {
    queue<PAIR > Q; // First : 사람의 index, Second : depth
    Q.push({ i,0 });
    int val = 0;
    int isvisited[101] = { false, };
    isvisited[i] = true;
    while (!Q.empty()) {
        int current = Q.front().X;        
        int mydepth = Q.front().Y;
        Q.pop();
        for (auto const& near : edge[current]) {
            if (isvisited[near])
                continue;
            val += mydepth + 1;
            Q.push({ near, mydepth + 1 });
            isvisited[near] = true;
        }
    }
    return val;
 
}
int main(void) {
    scanf("%d %d", &N, &M);
    while (M--) {
        int a, b;
        scanf("%d %d", &a, &b);
        edge[a].push_back(b);
        edge[b].push_back(a);
    }
    int mnidx = 1;
    int mnval = 0x7fffffff;
    for (int i = 1; i <= N; i++) {
        int val = KBvalue(i);
        if (val < mnval) {
            mnidx = i;
            mnval = val;
        }
    }
    printf("%d", mnidx);
}
