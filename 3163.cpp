#include <stdio.h>
#include <algorithm>
#define F first
#define S second
using namespace std;
typedef pair<int, int> ANT; // distance with end, ID
ANT ant[100001];
int ID[100001]; // position이 항상 증가하는 순으로 들어오므로 ID만 저장해도 됨
int main(void) {
    int T;
    scanf("%d", &T);
    while (T--) {
        int N, l, k;
        scanf("%d %d %d", &N, &l, &k);
        for (int i = 0; i < N; i++) {
            int a, p;
            scanf("%d %d", &p, &a);
            ID[i] = a;
            if (a < 0) { // dir이 왼쪽인경우
                ant[i].F = p + 1;
                ant[i].S = a;
            }
            else { // dir이 오른쪽인경우
                ant[i].F = l - p + 1;
                ant[i].S = a;
            }
        }
        sort(ant, ant + N);
        int left = 0; // 왼쪽에서 떨어지는 개미의 수
        int right = 0; // 오른쪽에서 떨어지는 개미의 수
        for (int i = 0; i < k-1; i++) {
            if (ant[i].S < 0) // 왼쪽으로 가는 개미라면
                left++;
            else // 오른쪽으로 가는 개미라면
                right++;
        }
        if (k <= N - 1 && ant[k - 1].F == ant[k].F) { // ant[k-1], ant[k]가 동시에 떨어지는 상황. ant[k-1].S < 0, ant[k].S > 0
            printf("%d\n", min(ID[left], ID[N - right - 1])); // ID[left-1] : ant[k-1], ID[N-right-1] : ant[k]
            continue;
        }
        if (k > 1 && ant[k - 1].F == ant[k - 2].F) { // ant[k-2].S < 0, ant[k-1].S > 0
            printf("%d\n", max(ID[left - 1], ID[N - right - 1])); // ID[left-1] : ant[k-2], ID[N-right] : ant[k-1]
            continue;
        }
 
        if (ant[k - 1].S < 0) // 왼쪽에서 떨어지는 개미라면
            printf("%d\n", ID[left]);
        else
            printf("%d\n", ID[N - right - 1]);
    }
}
