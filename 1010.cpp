#include <stdio.h>
int comb[31][31];
void comb_table(int n) {
    for (int i = 1; i <= n; i++) {
        comb[i][0] = 1; comb[i][i] = 1;
    }
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= i-1; j++) {
            comb[i][j] = comb[i - 1][j] + comb[i - 1][j - 1];
        }
    }
}
int main(void) {
    comb_table(30);
    int T;
    scanf("%d", &T);
    while (T--) {
        int N, M;
        scanf("%d %d", &N, &M);
        printf("%d\n", comb[M][N]);
    }
}
