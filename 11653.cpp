#include <stdio.h>
int main(void) {
    int N;
    scanf("%d", &N);
    int p = 2;
    while (p*p <= N) {
        if (N % p == 0) {
            printf("%d\n", p);
            N /= p;
        }
        else
            p++;
    }
    if (N != 1)
        printf("%d\n", N);
}
