#include <stdio.h>
typedef long long LL;
LL K, N;
LL lan[10000];
LL amount(LL len) {
    LL sum = 0;
    for (int i = 0; i < K; i++)
        sum += lan[i] / len;
    return sum;
}
int main(void) {
    scanf("%d %d", &K, &N);
    for (int i = 0; i < K; i++)
        scanf("%d", &lan[i]);
    LL st = 1;
    LL en = 0x80000000LL; // 답이 st~en-1 안에 있는 상태를 유지할 것임
    while (en - st > 1LL) {
        LL mid = (st + en) / 2;
        LL chunk = amount(mid);
        if (chunk >= N) // 크기가 mid인 조각이 N개 이상이면(답이 mid일 수도 있으므로 st = mid로 두어 범위를 mid~en-1로 축소)
            st = mid;
        else // 크기가 mid인 조각이 N개 미만이라면(답이 mid일 수가 없으므로 en = mid로 두어 범위를 st~mid-1로 축소)
            en = mid;
    }
    printf("%lld", st);
}
