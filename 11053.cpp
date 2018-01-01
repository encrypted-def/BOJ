#include <stdio.h>
#include <algorithm>
using namespace std;
int main(void) {
    int A[1001];
    int LIS[1001];
    int N;
    scanf("%d", &N);
    for (int i = 0; i < N; i++)
        scanf("%d", &A[i]);
    LIS[0] = A[0];
    int len = 1;
    for (int i = 0; i < N; i++) {
        if (A[i] > LIS[len - 1]) {
            LIS[len++] = A[i];
            continue;
        }
        int idx = lower_bound(LIS, LIS + len, A[i])-LIS;
        LIS[idx] = A[i];
    }
    printf("%d", len);
}
