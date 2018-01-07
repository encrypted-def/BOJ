#include <stdio.h>
 
int valid[9][9][9]; // valid[i][j] : 스도쿠상에서 (i, j)칸에 들어갈 수 있는 수의 목록
int valid_len[9][9]; // valid_len[i][j] : 스도쿠상에서 (i, j)칸에 들어갈 수 있는 수의 갯수
int sudoku[9][9];
int blank[81]; // (i, j)칸이 0일 경우 blank에 9*i+j를 저장
int blank_len = 0; // blank의 길이
int blank_conn[81][81]; // blank_conn[i] : blank[i]에게 blank[j]가 영향을 줄 수 있다고 할 때 j를 저장
int blank_conn_len[81] = { 0, };
int done = 0;
int area(int x, int y) {
    return (x / 3) * 3 + (y / 3);
}
 
void printsudoku() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++)
            printf("%d ", sudoku[i][j]);
        printf("\n");
    }
    printf("\n");
}
bool isrightsudoku() {
    for (int x = 0; x < 9; x++) {
        for (int y = 0; y < 9; y++) {
            int square = area(x, y);
            for (int i = 0; i < 9; i++) {
                if (sudoku[x][y] == sudoku[x][i] && y != i)
                    return false;
 
                if (sudoku[x][y] == sudoku[i][y] && x != i)
                    return false;
            }
            for (int i = (square / 3) * 3; i < (square / 3) * 3 + 3; i++) {
                for (int j = (square % 3) * 3; j < (square % 3) * 3 + 3; j++) {
                    if (sudoku[x][y] == sudoku[i][j] && (x != i || y != j))
                        return false;
                }
            }
        }
    }
    return true;
}
int brute_force(int idx) { // blank[idx]를 채우는 단계
                           // printf("%d ", idx);
    int x = blank[idx] / 9;
    int y = blank[idx] % 9;
    if (done)
        return 0;
    for (int i = 0; i < valid_len[x][y]; i++) {
        bool iscontradiction = false;
        sudoku[x][y] = valid[x][y][i];
        for (int j = 0; j < blank_conn_len[idx]; j++) { // i와 맞닿아있는 blank만 신경쓰면 됨
            if (sudoku[x][y] == sudoku[blank[blank_conn[idx][j]] / 9][blank[blank_conn[idx][j]] % 9]) {
                iscontradiction = true;
                break;
            }
        }
        if (iscontradiction) // 모순이 발생했으므로 다음 값을 sudoku[x][y]에 대입
            continue;
        // 여기까지 도달했다는 것은 인접한 것들과 아무런 문제가 없었다는 것
 
        //  printsudoku();
        // printf("%d\n", idx);
        if (idx < blank_len - 1)
            brute_force(idx + 1);
        if (idx == blank_len - 1 || done) {
            done = 1;
            return 0;
        }
    }
    sudoku[x][y] = 0; // 여기까지 도달했다는 것은 실패했다는 것
    return 0;
}
int main() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            scanf("%d", &sudoku[i][j]);
            if (sudoku[i][j] == 0)
                blank[blank_len++] = 9 * i + j;
        }
    }
    int cnt = 0;
    do {
        cnt = 0;
        for (int i = 0; i < blank_len; i++) {
            if (sudoku[blank[i] / 9][blank[i] % 9] > 0)
                continue;
            int x = blank[i] / 9;
            int y = blank[i] % 9;
            valid_len[x][y] = 0;
            int square = area(x, y);
            bool isavailable[10] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
            for (int j = 0; j < 9; j++) {
                isavailable[sudoku[x][j]] = false;
                isavailable[sudoku[j][y]] = false;
            }
            for (int j = (square / 3) * 3; j < (square / 3) * 3 + 3; j++) {
                for (int k = (square % 3) * 3; k < (square % 3) * 3 + 3; k++) {
                    isavailable[sudoku[j][k]] = false;
                }
            }
            for (int j = 1; j <= 9; j++) {
                if (isavailable[j])
                    valid[x][y][valid_len[x][y]++] = j;
            }
            if (valid_len[x][y] == 1) {
                sudoku[x][y] = valid[x][y][0];
                cnt++;
            }
        }
    } while (cnt > 0); // 확정지을 수 있는 칸은 모두 처리가 됨. 이제부터는 Brute force를 진행해야함
    blank_len = 0;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (sudoku[i][j] == 0) {
                blank[blank_len++] = 9 * i + j;
            }
        }
    }
    if (blank_len == 0) { // 빈 칸이 없을경우 출력 후 종료
        printsudoku();
        return 0;
    }
    for (int i = 0; i < blank_len; i++) {
        for (int j = i + 1; j < blank_len; j++) {
            if (blank[i] / 9 == blank[j] / 9 || blank[i] % 9 == blank[j] % 9 || area(blank[i] / 9, blank[i] % 9) == area(blank[j] / 9, blank[j] % 9)) {
                blank_conn[i][blank_conn_len[i]++] = j;
                blank_conn[j][blank_conn_len[j]++] = i;
            }
        }
    } // blank간의 connection 저장 완료
    brute_force(0);
    printsudoku();
}
