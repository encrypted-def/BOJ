#include <stdio.h>
int main(void) {
    int numa[100];
    int numb[100];
    numa[0] = 1;
    numb[0] = 0;
    for (int i = 1; i <= 50; i++) {
        numa[i] = numb[i - 1];
        numb[i] = numa[i - 1] + numb[i - 1];
    }
    int K;
    scanf("%d", &K);
    printf("%d %d", numa[K], numb[K]);
}
