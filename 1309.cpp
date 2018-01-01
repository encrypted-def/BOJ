#include <stdio.h>
#define MOD 9901
int D[100001];
int main(void) {
    int N;
    D[0] = 1;
    D[1] = 3;
 
    D[2] = D[1] + 2 * (D[0]) + 2;
    D[3] = D[2] + 2 * (D[1] + D[0]) + 2;
    D[4] = D[3] + 2 * (D[2] + D[1] + D[0]) + 2;
    int sum = D[0]+D[1];
    for (int i = 3; i <= 100000; i++) {
        D[i] = (D[i - 1] + 2 * sum + 2) % MOD;
        sum = (sum + D[i - 1]) % MOD;
    }
    scanf("%d", &N);
    printf("%d", D[N]);
}
