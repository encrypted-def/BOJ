#include <stdio.h>
typedef long long LL;
LL power(LL A, LL B, LL C) {
    if (B == 0)
        return 1;
    if (B == 1)
        return A % C;
    LL tmp = power(A, B / 2, C);
    if (B % 2 == 0)
        return (tmp*tmp) % C;
    else
        return (((tmp*tmp) % C) * A) % C;
}
int main(void) {
    LL A, B, C;
    scanf("%lld %lld %lld", &A, &B, &C);
    printf("%lld", power(A, B, C));
}
