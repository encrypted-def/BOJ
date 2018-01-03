#include <stdio.h>
#include <algorithm>
using namespace std;
 
typedef long long LL;
LL N;
LL budget[100000];
LL M;
LL D[100001]; // D[i] = budget[0] + budget[1] + ... + budget[i-1]
int main(void) {
    scanf("%lld", &N);
    for (int i = 0; i < N; i++)
        scanf("%lld", &budget[i]);
    scanf("%lld", &M);
    sort(budget, budget + N);
    D[0] = 0;
    for (int i = 1; i <= N; i++) 
        D[i] = D[i - 1] + budget[i-1];
    for (int i = 1; i <= N; i++) {
        if (D[i] + (N - i) * budget[i - 1] > M) { // i-1번쨰까진 예산을 전부 집행하고 그 이후로는 budget[i-1]로 한정된 예산을 집행했을 떄도 M을 초과할 경우 
            printf("%lld", (M - D[i - 1]) / (N - i + 1));
            return 0;
        }
    } // 모두 다 퍼줘도 예산이 넉넉하면 for문이 정상적으로 종료됨
    printf("%lld", budget[N - 1]);
}
