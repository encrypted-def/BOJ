#include <stdio.h>
int main(void) {
    int T;
    scanf("%d", &T);
    if (T % 10 != 0) {
        printf("-1");
        return 0;
    }
    int A = T / 300;
    T -= A * 300;
    int B = T / 60;
    T -= B * 60;
    printf("%d %d %d", A, B, T / 10);
}
