#include <stdio.h>
#include <tuple>
#include <algorithm>
using namespace std;
tuple<int, int, int> edge[100001]; // cost, com1, com2
int parent[1001]; // union-find에 쓰일 예정
int find(int i) { // find a root of i
    int root = i;
    while (parent[root] >= 0) {
        root = parent[root];
    }
    int child = i;
    while (child != root) {
        int tmp = parent[child];
        parent[child] = root;
        child = tmp;
    }
    return root;
}
void uni(int i, int j) {
    int tmp = parent[i] + parent[j];
    if (parent[i] > parent[j]) { // i가 가지고 있는 자식이 j가 가지고 있는 자식보다 적을 경우
        parent[i] = j; // j가 i의 root가 됨
        parent[j] = tmp; // j가 거느리는 자식이 많아짐
    }
    else {
        parent[j] = i; // i가 j의 root가 됨
        parent[i] = tmp; // j가 거느리는 자식이 많아짐
    }
}
int main(void) {
    int N, M;
    scanf("%d %d", &N, &M);
    for (int i = 1; i <= N; i++)
        parent[i] = -1;
    for (int i = 0; i < M; i++) {
        scanf("%d %d %d", &get<1>(edge[i]), &get<2>(edge[i]), &get<0>(edge[i]));
 
    }
    sort(edge, edge + M);
    int cnt = 0;
    int cost = 0;
    int idx = 0;
    while (cnt < N - 1) {
        if (find(get<1>(edge[idx])) == find(get<2>(edge[idx]))) { // com1과 com2가 이미 묶여있으면
            idx++; continue;
        }
        //묶여있지 않으면
        uni(find(get<1>(edge[idx])), find(get<2>(edge[idx])));
        cost += get<0>(edge[idx]);
        cnt++;
    }
    printf("%d", cost);
}
