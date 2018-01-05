#include <stdio.h>
int state[3][50]; // state[0][i] : i번쨰 column에 말이 있는지 없는지
                  // state[1][i] : i번쨰 대각선에(/ 방향) 말이 있는지 없는지
                  // state[2][i] : i번째 대각선에(\ 방향) 말이 있는지 없는지
int cnt = 0;
int N;
void board_recursive(int current) { // current번째 row에 말을 배치할 예정임
 
    if (current == N) {
        cnt++;
        return;
    }
    for (int i = 0; i < N; i++) { // (i, current)에 퀸을 놓을 예정
        if (state[0][i] || state[1][i + current] || state[2][current - i + N])
            continue;
        state[0][i] = true;
        state[1][i + current] = true;
        state[2][current - i + N] = true;
        board_recursive(current + 1);
        state[0][i] = false;
        state[1][i + current] = false;
        state[2][current - i + N] = false;
    }
}
int main(void) {
    scanf("%d", &N);
    board_recursive(0);
    printf("%d", cnt);
}
