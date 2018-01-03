#include <stdio.h>
#include <algorithm>
using namespace std;
int LIS[201]; // LIS를 저장할 array
int main(void) {
    int N;
    int num[201];
    int idx = 0; // LIS에서 사용할 index
    scanf("%d", &N);
    for (int i = 0; i < N; i++)
        scanf("%d", &num[i]);
    LIS[0] = num[0];
    idx++;
    for (int i = 0; i < N; i++) {
        if (LIS[idx - 1] < num[i]) {
            LIS[idx] = num[i];
            idx++;
        }
        else
            *lower_bound(LIS, LIS + idx, num[i]) = num[i];
    }
    printf("%d", N - idx);
}
