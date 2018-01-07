#include <stdio.h>
#include <algorithm>
using namespace std;
typedef pair<int, int> PAIR;
#define X first
#define Y second
int N, M;
int card[500003];
PAIR query[500003];
int ans[500003];
int main(void) {
    scanf("%d", &N);
    for (int i = 0; i < N; i++)
        scanf("%d", &card[i]);
    scanf("%d", &M);
    for (int i = 0; i < M; i++) {
        scanf("%d", &query[i].X);
        query[i].Y = i;
    }
    sort(card, card + N);
    sort(query, query + M);
    int idx1 = 0;
    int idx2 = 0;
    while (idx1 < N && idx2 < M) {
        if (idx2 != 0 && query[idx2].X == query[idx2 - 1].X) {
            ans[query[idx2].Y] = ans[query[idx2 - 1].Y];
            idx2++;
            continue;
        }
        if (card[idx1] < query[idx2].X)
            idx1++;
        else if (card[idx1] > query[idx2].X)
            idx2++;
        else {
            ans[query[idx2].Y]++;
            idx1++;
        }
    }
    idx2++;
    while (idx2 < M) {
        if (idx2 != 0 && query[idx2].X == query[idx2 - 1].X) {
            ans[query[idx2].Y] = ans[query[idx2 - 1].Y];
            idx2++;
        }
        else
            break;
    }
    for (int i = 0; i < M; i++)
        printf("%d ", ans[i]);
}
