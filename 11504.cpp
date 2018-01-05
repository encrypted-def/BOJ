#include <stdio.h>
#include <algorithm>
using namespace std;
int A[1001];
int D1[1001]; // D1[i] = A[i]를 포함하는 LIS의 길이(A[0] to A[i]에서 생각)
int D2[1001]; // D2[i] = A[i]를 포함하는 LDS의 길이(A[i] to A[N-1]에서 생각)
int N;
int main(void) {
    scanf("%d", &N);
    for (int i = 0; i < N; i++)
        scanf("%d", &A[i]);
    D1[0] = 1;
    for (int i = 1; i < N; i++) {
        D1[i] = 1;
        for (int j = 0; j < i; j++) {
            if (A[i] > A[j])
                D1[i] = max(D1[i], D1[j] + 1);
        }
    }
    D2[N - 1] = 1;
    for (int i = N - 2; i >= 0; i--) {
        D2[i] = 1;
        for (int j = N - 1; j > i; j--) {
            if (A[i] > A[j])
                D2[i] = max(D2[i], D2[j] + 1);
        }
    }
    int mx = 0;
    for (int i = 0; i < N; i++)
        mx = max(mx, D1[i] + D2[i]-1);
    printf("%d", mx);
}
