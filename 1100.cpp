#include <stdio.h>
int main(void) {
    char board[10][10];
    for (int i = 0; i < 8; i++)
        scanf("%s", board[i]);
    int cnt = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j ++)
            cnt += (board[i][j] == 'F' && (i+j) % 2 == 0);
    }
    printf("%d", cnt);
}
