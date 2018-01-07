#include <stdio.h>
#include <algorithm>
#include <vector>
using namespace std;
typedef pair<int, int> PAIR;
#define X first
#define Y second
int N;
int D[10004]; // D[i] : i를 root로 하는 subtree에 속한 node 중에서 i로부터 가장 멀리 떨어진 것과의 거리
int mx = 0;
vector<PAIR> child[10004]; // child[i] : i의 자식들 (node 번호, edge 길이)
void calc(int i) {
    D[i] = 0;
    int fi = -1; // i를 root로 하는 subtree에 속한 node 중 i와 가장 멀리 떨어진 것의 거리
    int se = -1; // i를 root로 하는 subtree에 속한 node 중 i와 두번째로 멀리 떨어진 것의 거리 
    for (PAIR c : child[i]) {
        if (D[c.X] == -1) // 아직 방문하지 않았다면
            calc(c.X);
        int cur_dist = D[c.X] + c.Y;
        D[i] = max(D[i], cur_dist); // D[i] 갱신
        if (fi < cur_dist) { // 제일 긴게 갱신된다면
            se = fi;
            fi = cur_dist;
        }
        else if (se < cur_dist) // 두번쨰로 긴게 갱신된다면
            se = cur_dist;
    }
    if (se != -1) { // 자식이 2명 이상이라면        
        mx = max(mx, fi + se); // mx를 갱신
    }
}
int main(void) {
    scanf("%d", &N);
    fill(D, D + N, -1);
    for (int i = 0; i < N - 1; i++) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        child[a].push_back({ b,c });
    }
    calc(1);
    for (int i = 1; i <= N; i++)
        mx = max(mx, D[i]); // subtree의 자식과 자기 자신이 지름이 될 수 있으므로 추가해줘야함
    printf("%d", mx);
}
