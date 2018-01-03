#include <stdio.h>
#include <algorithm>
using namespace std;
int D[1003];
int main(void) {
    int A[1003];
    int N;
    scanf("%d", &N);
    for (int i = 0; i < N; i++)
        scanf("%d", &A[i]);
    
    D[0] = A[0];
    int mx = D[0];
    for (int i = 1; i < N; i++) {
        D[i] = A[i];
        for (int j = 0; j < i; j++) {
            if (A[j] >= A[i])
                continue;
            D[i] = max(D[i], D[j] + A[i]);
        }
        mx = max(mx, D[i]);
    }
    printf("%d", mx);
}
