#include <stdio.h>
#include <algorithm>
using namespace std;
int N, M;
int card[500001];
int main(void) {
    scanf("%d", &N);
    for (int i = 0; i < N; i++)
        scanf("%d", &card[i]);
    sort(card, card + N);
    scanf("%d", &M);
    while (M--) {
        int num;
        scanf("%d", &num);
        printf("%d ", binary_search(card, card + N, num));
    }
}
