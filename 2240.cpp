#include <stdio.h>
#include <algorithm>
using namespace std;
int D[1003][31][2]; // D[i][j][k] : i초동안 j번 움직여서 얻을 수 있는 자두의 최대 갯수(마지막에 자두는 k번 자두나무 아래에 위치해있음)
int num[1004];
int main(void) {
    int T, W;
    scanf("%d %d", &T, &W);
    for (int i = 1; i <= T; i++) {
        scanf("%d", &num[i]);
        num[i]--; // 처리를 편하게 하기 위해 나무 번호를 0/1로 저장함
    }
    
 
    D[0][0][0] = 0;
    D[0][0][1] = 0;
    for (int i = 1; i <= T; i++) {
        D[i][0][0] = D[i - 1][0][0] + (num[i] == 0);
        for (int j = 1; j <= W; j++) {
            if (i < j) // i초에 i번 이상 위치를 바꾸는건 불가능함
                continue;
            if (j % 2 == 0) // 반드시 1번 나무에서 0번 나무로 이동해와야하는 상황
                D[i][j][0] = max(D[i - 1][j - 1][1], D[i-1][j][0]) + (num[i] == 0);
            else // 반드시 0번 나무에서 1번 나무로 이동해와야하는 상황
                D[i][j][1] = max(D[i - 1][j - 1][0], D[i-1][j][1]) + (num[i] == 1);
 
        }
    }
    int mx = 0;
    for (int j = 0; j <= W; j++) {
        mx = max(mx, D[T][j][1]);
        mx = max(mx, D[T][j][0]);
    }
    printf("%d", mx);
}
