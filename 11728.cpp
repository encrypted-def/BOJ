#include <stdio.h>
int N, M;
int A[1000001];
int B[1000001];
int idx1, idx2;
int main(void) {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; i++)
        scanf("%d", &A[i]);
    for (int i = 0; i < M; i++)
        scanf("%d", &B[i]);
    while (idx1 + idx2 < N + M) {
        if (idx1 == N)
            printf("%d ", B[idx2++]);
        else if (idx2 == M)
            printf("%d ", A[idx1++]);
        else {
            if (A[idx1] > B[idx2])
                printf("%d ", B[idx2++]);
            else
                printf("%d ", A[idx1++]);
        }
    }
}
