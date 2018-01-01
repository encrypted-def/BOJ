#include <stdio.h>
#define MOD 10007
int main(void) {
    int D[1003];
    D[1] = 1;
    D[2] = 3;
    for (int i = 3; i <= 1000; i++)
        D[i] = (D[i - 1] + 2*D[i - 2]) % MOD;
    int n;
    scanf("%d", &n);
    printf("%d", D[n]);
}
