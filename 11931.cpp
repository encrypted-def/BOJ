#include <stdio.h>
int N;
int num[2000003];
int main(void) {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        int t;
        scanf("%d", &t);
        num[t + 1000000] = 1;
    }
    for (int i = 2000000; i >= 0; i--) {
        if (num[i] == 1)
            printf("%d\n", i - 1000000);
    }
}
