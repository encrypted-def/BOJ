#include <stdio.h>
#include <algorithm>
using namespace std;
int D[101][101]; // D[i][j] : i에서 j로 가는 최소비용
int main(void) {
    int n, m;
    scanf("%d %d", &n, &m);
    while (m--) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        if (D[a][b] == 0)
            D[a][b] = c;
        else
            D[a][b] = min(D[a][b], c);
    }
    for (int chk = 1; chk <= n; chk++) {
        for (int st = 1; st <= n; st++) {
            for (int en = 1; en <= n; en++) {
                if (st == en)
                    continue;
                if (D[st][chk] == 0 || D[chk][en] == 0)
                    continue;
                if (D[st][en] == 0)
                    D[st][en] = D[st][chk] + D[chk][en];
                else
                    D[st][en] = min(D[st][en], D[st][chk] + D[chk][en]);
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++)
            printf("%d ", D[i][j]);
        printf("\n");
    }
}
