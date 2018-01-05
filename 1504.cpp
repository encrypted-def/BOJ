#include <stdio.h>
#include <algorithm>
using namespace std;
int dist[801][801];
int N, E;
int v1, v2;
void set_dist(void) {
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++)
            dist[i][j] = 0xfffffff;
        dist[i][i] = 0;
    }
}
int main(void) {
    scanf("%d %d", &N, &E);
    set_dist();
    while (E--) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        dist[a][b] = c;
        dist[b][a] = c;
    }
    scanf("%d %d", &v1, &v2);
    for (int k = 1; k <= N; k++) {
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
    int ans = min(dist[1][v1] + dist[v1][v2] + dist[v2][N], dist[1][v2] + dist[v1][v2] + dist[v1][N]);
    if (ans > 0xfffffff)
        printf("-1");
    else
        printf("%d", ans);
}
