#include <stdio.h>
void print_state(int st, int en) {
    printf("%d %d\n", st, en);
}
void hanoi(int st, int en, int N) {
    if (N == 1) {
        print_state(st, en);
        return;
    }
    hanoi(st, 6 - st - en, N-1);
    print_state(st, en);
    hanoi(6 - st - en, en, N - 1);
}
int main(void) {
    int K;
    scanf("%d", &K);
    printf("%d\n", (1 << K) - 1);
    hanoi(1, 3, K);
}
