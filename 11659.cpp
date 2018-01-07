#include <stdio.h>
int segment[400000];
int update(int i, int val, int node, int node_st, int node_en) {
    if (node_st > i || i > node_en) // i번째 값을 입력받았는데 node_st~node_en 범위 안에 i가 없을 경우
        return segment[node];
    if (node_st == node_en) // leaf에 도달한 경우
        return segment[node] = val;
    int mid = (node_st + node_en) / 2;
    return segment[node] = (update(i, val, node * 2, node_st, mid) + update(i, val, node * 2 + 1, mid + 1, node_en));
}
int query(int a, int b, int node, int node_st, int node_en) {
    if (node_en < a || b < node_st) // a~b와 node_st~node_en 범위가 아예 겹치지 않는 경우
        return 0;
    if (a <= node_st && node_en <= b) // node_st~node_en 범위가 a~b 범위 안에 완벽하게 들어가는 경우
        return segment[node];
    int mid = (node_st + node_en) / 2;
    return query(a, b, node * 2, node_st, mid)+query(a, b, node * 2 + 1, mid + 1, node_en);
}
 
int main(void) {
    int N, M;
    scanf("%d %d", &N, &M);
    for (int i = 1; i <= N; i++) {
        int a;
        scanf("%d", &a);
        update(i, a, 1, 1, N);
    }
    while (M--) {
        int a, b;
        scanf("%d %d", &a, &b);
        printf("%d\n", query(a, b, 1, 1, N));
    }
}
