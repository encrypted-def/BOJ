#include <stdio.h>
#include <algorithm>
using namespace std;
int N, C;
int x[200005];
 
bool isPossibleDist(int dist) { // 공유기 사이의 거리를 dist로 하는 것이 가능한지
    int cnt = 1;
    int cur = x[0];
    for (int i = 1; i < N; i++) {
        if (x[i] - cur >= dist) {
            cnt++;
            cur = x[i]; // x[i]에 공유기 설치
        }
    }
    return cnt >= C;
}
int main(void) {
    scanf("%d %d", &N, &C);
    for (int i = 0; i < N; i++) 
        scanf("%d", &x[i]);
    sort(x, x + N);
    int lo = 1;
    int hi = 1000000000; // lo~hi-1 안에 답이 존재
    while (hi > lo + 1) { // 이분탐색
        int mid = (lo + hi) / 2;
        if (isPossibleDist(mid)) // 공유기 간 거리가 mid일 때 C개 이상 설치 가능하다면
            lo = mid; // 거리를 늘려볼 것임
        else // 공유기 간 거리가 mid일 때 C개 이상 설치할 수 없다면
            hi = mid; // 거리를 줄임
    }
    printf("%d", lo);
}
