#include <stdio.h>
#include <algorithm>
using namespace std;
int N, S;
int num[100003];
int D[100003]; // D[i] : num[1]+num[2]...+num[i]
int main(void) {
    scanf("%d %d", &N, &S);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &num[i]);
        D[i] = D[i - 1] + num[i];
    }
    int min_len = 100001;
    for (int st_idx = 1; st_idx <= N; st_idx++) { // D[i] - D[st_idx-1] >= S인 최소의 i를 찾을 예정
        int i = distance(D, lower_bound(D, D + N + 1, S + D[st_idx - 1]));
        if (i > N)
            continue;
        min_len = min(min_len, i - st_idx + 1);
    }
    if (min_len == 100001)
        min_len = 0;
    printf("%d", min_len);
}
