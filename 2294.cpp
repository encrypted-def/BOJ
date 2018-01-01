#include <stdio.h>
#include <algorithm>
int coin[101];
int D[10001];
using namespace std;
int main(void) {
    int n, k;
    scanf("%d %d", &n, &k);
    for (int i = 0; i <= k; i++)
        D[i] = 0x7ffffff;
    for (int i = 0; i < n; i++)
        scanf("%d", &coin[i]);
    for (int i = 0; i < n; i++) {
        if (coin[i] > k)
            continue;
        D[coin[i]] = 1;
        for (int j = coin[i] + 1; j <= k; j++) 
            D[j] = min(D[j], D[j - coin[i]] + 1);
    }
    if (D[k] == 0x7ffffff)
        D[k] = -1;
    printf("%d", D[k]);
}
