#include <stdio.h>
#include <algorithm>
using namespace std;
int A[3][10003];
int B[3][10003];
int C[3][10003];
int D[3][10003];
int enemy[2][10003];
void set_table(int arr[][10003], int st, int en, int W) {
    for (int i = st; i < en; i++) {
        arr[1][i] = arr[0][i - 1] + 1;
        if (enemy[0][i - 1] + enemy[0][i] <= W)
            arr[1][i] = min(arr[1][i], arr[2][i - 1] + 1);
        arr[2][i] = arr[0][i - 1] + 1;
        if (enemy[1][i - 1] + enemy[1][i] <= W)
            arr[2][i] = min(arr[2][i], arr[1][i - 1] + 1);
        arr[0][i] = arr[2][i] + 1; // (0, i)를 기준으로 삼음
        if (enemy[0][i] + enemy[1][i] <= W)
            arr[0][i] = min(arr[0][i], arr[0][i - 1] + 1);
        if (enemy[0][i] + enemy[0][i - 1] <= W) {
            arr[0][i] = min(arr[0][i], arr[2][i - 1] + 2);
            if (enemy[1][i] + enemy[1][i - 1] <= W) {
                if (i == 1)
                    arr[0][i] = 2;
                else
                    arr[0][i] = min(arr[0][i], arr[0][i - 2] + 2);
            }
        }
    }
}
int main(void) {
    int T;
    scanf("%d", &T);
    while (T--) {
        int N, W;
        scanf("%d %d", &N, &W);
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < N; j++)
                scanf("%d", &enemy[i][j]);
        if (N == 1) {
            int ans = 2;
            if (enemy[0][0] + enemy[1][0] <= W)
                ans = 1;
            printf("%d\n", ans);
            continue;
        }
        if (N == 2) {
            int ans = 4;
            if (enemy[0][0] + enemy[0][1] <= W || enemy[1][0]+enemy[1][1] <= W || enemy[0][0] + enemy[1][0] <= W || enemy[0][1]+enemy[1][1] <= W)
                ans = 3;
            if (enemy[0][0] + enemy[0][1] <= W && enemy[1][0] + enemy[1][1] <= W)
                ans = 2;
            if (enemy[0][0] + enemy[1][0] <= W && enemy[0][1] + enemy[1][1] <= W)
                ans = 2;
            printf("%d\n", ans);
            continue;
        } // N이 작을 때에는 바로 처리
 
        A[1][0] = 1;
        A[2][0] = 1;
        if (enemy[0][0] + enemy[1][0] <= W)
            A[0][0] = 1;
        else
            A[0][0] = 2; // A의 초기값 설정
        set_table(A, 1, N, W); // A의 dynamic table 채움
        B[0][0] = 1;
        B[0][1] = 3;
        if (enemy[0][0] + enemy[0][1] <= W)
            B[0][1] = 2;
        if (enemy[0][1] + enemy[1][1] <= W)
            B[0][1] = 2;
        B[1][1] = 2;
        if (enemy[0][0] + enemy[0][1] <= W)
            B[1][1] = 1;
        B[2][1] = 2; // B의 초기값 설정
        set_table(B, 2, N, W); // B의 dynamic table 채움
        C[0][0] = 1;
        C[0][1] = 3;
        if (enemy[1][0] + enemy[1][1] <= W)
            C[0][1] = 2;
        if (enemy[0][1] + enemy[1][1] <= W)
            C[0][1] = 2;
        C[1][1] = 2;
        C[2][1] = 2;
        if (enemy[1][0] + enemy[1][1] <= W)
            C[2][1] = 1; // C의 초기값 설정
        set_table(C, 2, N, W); // C의 dynamic table 채움
        D[0][1] = 2;
        if (enemy[0][1] + enemy[1][1] <= W)
            D[0][1] = 1;
        D[1][1] = 1;
        D[2][1] = 1; //D의 초기값 설정
        set_table(D, 2, N, W); // D의 dynamic table 채움
        int ans = A[0][N - 1];
        if (enemy[0][0] + enemy[0][N - 1] <= W)
            ans = min(ans, C[2][N - 1] + 1);
        if (enemy[1][0] + enemy[1][N - 1] <= W)
            ans = min(ans, B[1][N - 1] + 1);
        if (enemy[0][0] + enemy[0][N - 1] <= W && enemy[1][0] + enemy[1][N - 1] <= W)
            ans = min(ans, D[0][N - 2] + 2);
        printf("%d\n", ans);
    }
}
