#include <stdio.h>
bool isPalindrome[2002][2002];
int num[2002];
int main(void) {
    int N, M;
    scanf("%d", &N);
    for (int i = 1; i <= N; i++)
        scanf("%d", &num[i]);
    scanf("%d", &M);
    for (int i = 1; i <= N; i++) {
        isPalindrome[i][i] = true;
        isPalindrome[i][i+1] = num[i] == num[i+1];
    }
    for (int sz = 3; sz <= N; sz++) {
        for (int i = 1; i <= N - sz + 1; i++)
            isPalindrome[i][i + sz - 1] = ((isPalindrome[i + 1][i + sz - 2]) && (num[i] == num[i + sz - 1]));
    }
    while (M--) {
        int S, E;
        scanf("%d %d", &S, &E);
        printf("%d\n", isPalindrome[S][E]);
    }
}
