#include <stdio.h>
int rank[1000003];
int parent[1000003];
 
int find(int u) {
    if (u == parent[u]) return u;
    return parent[u] = find(parent[u]);
}
void merge(int u, int v) {
    u = find(u); v = find(v);
    if (u == v) return;
    if (rank[u] > rank[v]) {
        int t = u;
        u = v;
        v = t;
    }
    parent[u] = v;
    if (rank[u] == rank[v]) ++rank[v];
}
int main(void) {
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 0; i <= n; i++) {
        rank[i] = 1;
        parent[i] = i;
    }
    while (m--) {
        int op, a, b;
        scanf("%d %d %d", &op, &a, &b);
        if (op == 0)
            merge(a, b);
        
        if (op == 1) {
            if (find(a) == find(b))
                printf("YES\n");
            else
                printf("NO\n");
        }
    }
}
