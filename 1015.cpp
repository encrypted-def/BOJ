#include <stdio.h>
#include <algorithm>
using namespace std;
typedef pair<int, int> PAIR;
PAIR num[60];
int main(void) {
    int N;
    int P[60];
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &num[i].first);
        num[i].second = i;
    } // (2, 0), (3, 1), (1, 2)
    sort(num, num + N);
    for (int i = 0; i < N; i++)
        P[num[i].second] = i;;
    for (int i = 0; i < N; i++)
        printf("%d ", P[i]);
}
