#include <stdio.h>
int conv(int n) {
    if (n == 0)
        return 10;
    return n;
}
int pow(int a, int b) {
    if (b == 1)
        return conv(a % 10);
    int tmp = pow(a, b / 2);
    if (b % 2 == 0)
        return conv(tmp*tmp % 10);
    if (b % 2 != 0)
        return conv(tmp*tmp * a % 10);
}
int main(void) {
    int T;
    scanf("%d", &T);
    while (T--) {
        int a, b;
        scanf("%d %d", &a, &b);
        printf("%d\n", pow(a, b));
    }
}
