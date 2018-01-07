#include <stdio.h>
typedef long long LL;
int isSqFree[1000001];
int main(void) {
    LL a, b;
    scanf("%lld %lld", &a, &b);
    for (int i = 0; i < b - a + 1; i++)
        isSqFree[i] = true;
    for (LL sq = 2; sq <= 1000000; sq++) {
        if (b < sq*sq) // b보다 sq*sq가 크다면
            break; // 앞으로는 sq*sq의 배수가 있는지 확인할 필요가 없음
        for (LL i = a / (sq*sq); i*sq*sq <= b; i++) {
            if (sq*sq*i >= a) // sq*sq의 배수가 a~b사이에 있는거면
                isSqFree[sq*sq*i - a] = false;
        }
    }
    int cnt = 0;
    for (int i = 0; i < b - a + 1; i++)
        cnt += isSqFree[i];
    printf("%d", cnt);
}
