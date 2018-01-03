#include <stdio.h>
#include <algorithm>
using namespace std;
typedef long long LL;
int A[10001];
int N, M;
LL D[10001]; // D[i] = A[0] + A[1] + A[2] + .. + A[i-1]
int main(void) {
    int N;
    LL M;
    scanf("%d %lld", &N, &M);
    for (int i = 0; i < N; i++)
        scanf("%d", &A[i]);
    for (int i = 1; i <= N; i++) {
        D[i] = D[i - 1] + A[i-1];
    }
    int cnt = 0;
    for (int i = 1; i <= N; i++) // D[i]에 대해서 D[j] = D[i]-M를 만족하는 j가 있는지 탐색할 것임
        cnt += binary_search(D, D + i, D[i]-M);
    printf("%d", cnt);
}
