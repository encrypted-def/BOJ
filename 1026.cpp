#include <stdio.h>
#include <algorithm>
#include <functional>
using namespace std;
int main(void) {
    int N;
    int A[52];
    int B[52];
    scanf("%d", &N);
    for (int i = 0; i < N; i++)
        scanf("%d", &A[i]);
    for (int i = 0; i < N; i++)
        scanf("%d", &B[i]);
    sort(A, A + N, greater<int>() );
    sort(B, B + N);
    int sum = 0;
    for (int i = 0; i < N; i++) sum += A[i] * B[i];
    printf("%d", sum);
}
