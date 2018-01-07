#include <stdio.h>
#include <algorithm>
using namespace std;
int maxseg[4 * 100000], minseg[4 * 100000];
int maxupdate(int i, int val, int node, int node_st, int node_en) {
    if (node_st > i || i > node_en) // i번째 값을 입력받았는데 node_st~node_en 범위 안에 i가 없을 경우
        return maxseg[node];
    if (node_st == node_en) // leaf에 도달한 경우
        return maxseg[node] = val;
    int mid = (node_st + node_en) / 2;
    return maxseg[node] = max(maxupdate(i, val, node * 2, node_st, mid), maxupdate(i, val, node * 2 + 1, mid + 1, node_en));
}
int maxquery(int a, int b, int node, int node_st, int node_en) {
    if (node_en < a || b < node_st) // a~b와 node_st~node_en 범위가 아예 겹치지 않는 경우
        return -1;
    if (a <= node_st && node_en <= b) // node_st~node_en 범위가 a~b 범위 안에 완벽하게 들어가는 경우
        return maxseg[node];
    int mid = (node_st + node_en) / 2;
    return max(maxquery(a, b, node * 2, node_st, mid), maxquery(a, b, node * 2 + 1, mid + 1, node_en));
}
int minupdate(int i, int val, int node, int node_st, int node_en) {
    if (node_st > i || i > node_en) // i번째 값을 입력받았는데 node_st~node_en 범위 안에 i가 없을 경우
        return minseg[node];
    if (node_st == node_en) // leaf에 도달한 경우
        return minseg[node] = val;
    int mid = (node_st + node_en) / 2;
    return minseg[node] = min(minupdate(i, val, node * 2, node_st, mid), minupdate(i, val, node * 2 + 1, mid + 1, node_en));
}
int minquery(int a, int b, int node, int node_st, int node_en) {
    if (node_en < a || b < node_st) // a~b와 node_st~node_en 범위가 아예 겹치지 않는 경우
        return 0x7fffffff;
    if (a <= node_st && node_en <= b) // node_st~node_en 범위가 a~b 범위 안에 완벽하게 들어가는 경우
        return minseg[node];
    int mid = (node_st + node_en) / 2;
    return min(minquery(a, b, node * 2, node_st, mid), minquery(a, b, node * 2 + 1, mid + 1, node_en));
}
int main(void) {
    int N, M;
    scanf("%d %d", &N, &M);
    for (int i = 1; i <= N; i++) {
        int t;
        scanf("%d", &t);
        maxupdate(i, t, 1, 1, N);
        minupdate(i, t, 1, 1, N);
    }
    while (M--) {
        int a, b;
        scanf("%d %d", &a, &b);
        printf("%d %d\n", minquery(a, b, 1, 1, N), maxquery(a, b, 1, 1, N));
    }
    return 0;
}
