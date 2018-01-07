#include <stdio.h>
void solve(int N, bool isNegative) {
    if (N == 0)
        return;
    if (N == 1 && !isNegative) {
        printf("1");
        return;
    }
    if (N == 1 && isNegative) {
        printf("11");
        return;
    }
    if (N % 2 == 0) {
        solve(N / 2, !isNegative);
        printf("0");
    }
    else {
        if (!isNegative) // 다음 digit은 negative
            solve((N - 1) / 2, !isNegative);
        else
            solve((N + 1) / 2, !isNegative);
        printf("1");
    }
    
}
int main(void) {
    int N;
    scanf("%d", &N);
    if (N == 0)
        printf("0");
    else
        solve(N, 0);
}
