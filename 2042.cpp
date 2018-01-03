#include <stdio.h>
#define MAX_N 1000000
typedef long long LL;
LL BIT[MAX_N + 1];
LL num[MAX_N + 1];
void add(int idx, LL val) {
    while (idx <= MAX_N) {
        BIT[idx] += val;
        idx += (idx & -idx);
    }
}
 
LL sum(int idx) {
    LL s = 0;
    while (idx > 0) {
        s += BIT[idx];
        idx -= (idx & -idx);
    }
    return s;
}
 
int main(void) {
    int N, M, K;
    scanf("%d %d %d", &N, &M, &K);
    for (int i = 1; i <= N; i++) {
        scanf("%lld", &num[i]);
        add(i, num[i]);
    }
    for (int i = 0; i < M + K; i++) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        if (a == 1) {
            add(b, c - num[b]);
            num[b] = c;
        }
        else 
            printf("%lld\n", sum(c) - sum(b - 1));
    }
}
