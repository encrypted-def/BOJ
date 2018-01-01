#include <string.h>
#include <stdio.h>
int main(void) {
    int N;
    scanf("%d", &N);
    char name[53][53];
    for (int i = 0; i < N; i++)
        scanf("%s", name[i]);
    int len = strlen(name[0]);
    int cnt = 0;
    char ans[53] = { 0, };
    for (int i = 0; i < len; i++) {
        ans[i] = name[0][i];
        for (int j = 1; j < N; j++) {
            if (name[0][i] != name[j][i]) {
                ans[i] = '?';
                break;
            }
        }
    }
    printf("%s", ans);
}
