#include <stdio.h>
#include <algorithm>
using namespace std;
int D[1004]; // D[i] : i번째 칸에 도달하기 위한 최소 점프 횟수
int A[1004];
int main(void) {
    int N;
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
        D[i] = 0x7ffff;
    }
    D[0] = 0;
    for (int i = 0; i < N; i++) {
        for (int j = i; j <= i + A[i]; j++) {
            if (j >= N)
                break;
            D[j] = min(D[j], D[i] + 1);
        }
    }
    if (D[N - 1] >= 0x7ffff)
        printf("-1");
    else
        printf("%d", D[N - 1]);
 
}
