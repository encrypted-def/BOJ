#include <stdio.h>
void blank(int n) {
    while (n--) printf(" ");
}
void star(int n) {
    while (n--) printf("*");
}
int main(void) {
    int N;
    scanf("%d", &N);
    for (int h = 1; h <= N; h++) {
        blank(N - h);
        star(2 * h - 1);
        printf("\n");
    }
}
