#include <stdio.h>
#include <queue>
using namespace std;
int level[100001];
int main(void) {
    int N, K;
    scanf("%d %d", &N, &K);
    queue<int> Q;
    Q.push(N);
    level[N] = 1;
    if (N == K) {
        printf("0");
        return 0;
    }
    while (true) {
        int cur = Q.front(); Q.pop();
        int arr[3] = { cur + 1, cur - 1, cur * 2 };
        for (int i = 0; i < 3; i++) {
            if (arr[i] < 0 || arr[i] > 100000)
                continue;
            if (level[arr[i]] != 0)
                continue;
            if (arr[i] == K) {
                printf("%d", level[cur]);
                return 0;
            }
            level[arr[i]] = level[cur] + 1;
            Q.push(arr[i]);
        }
    }
}
