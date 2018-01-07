#include <stdio.h>
#include <algorithm>
using namespace std;
typedef pair<int, int> PAIR;
#define X first
#define Y second
PAIR num[500004];
int N;
int main(void) {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &num[i].X);
        num[i].Y = i;
    }
    sort(num, num + N);
    int cnt = 0;
    for (int i = 0; i < N; i++)
        cnt = max(num[i].Y - i, cnt);
    printf("%d", cnt+1);
}
