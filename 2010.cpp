#include <stdio.h>
int main(void) {
    int N;
    scanf("%d", &N);
    int cnt = 1;
    while (N--) {
        int t;
        scanf("%d", &t);
        cnt += t - 1;
    }
    printf("%d", cnt);
}
