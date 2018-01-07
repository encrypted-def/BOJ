#include <stdio.h>
int D[101][101][201][2]; // D[i][j][t][d]. t : 턴 횟수 d : 0 - from right, 1 - from upward
int main(void){
    int T;
    scanf("%d", &T);
    while(T--){
        int row[101][101];
        int col[101][101];
        int M, N, L, G;
        scanf("%d %d %d %d", &M, &N, &L, &G);
        int maxturn = N < M ? 2*N : 2*M;
        for(int i = 0; i < M; i++){
            for(int j = 0; j < N; j++){
                for(int t = 0; t <= maxturn; t++){
                    D[i][j][t][0] = 0xfffffff;
                    D[i][j][t][1] = 0xfffffff;
                }
            }
        }
        for(int i = 0; i < M; i++){
            for(int j = 1; j < N; j++)
                scanf("%d", &row[i][j]);
        }
        for(int i = 1; i < M; i++){
            for(int j = 0; j < N; j++)
                scanf("%d", &col[i][j]);
        }
        // D[0~1][0~1][][]인 경우 별도 처리
        D[0][0][0][0] = 0;
        D[0][0][0][1] = 0;
        for(int i = 1; i < M; i++)
            D[i][0][0][1] = col[i][0] + D[i-1][0][0][1];
        for(int i = 1; i < N; i++)
            D[0][i][0][0] = row[0][i] + D[0][i-1][0][0];
        // D[1~M-1][1~N-1] 처리
        for(int i = 1; i < M; i++){
            for(int j = 1; j < N; j++){
                int range = i < j ? 2*i : 2*j;
                for(int t = 1; t <= range; t++){
                    D[i][j][t][0] = D[i][j-1][t][0] < D[i][j-1][t-1][1] ? D[i][j-1][t][0]+row[i][j] : D[i][j-1][t-1][1]+row[i][j];  
                    D[i][j][t][1] = D[i-1][j][t-1][0] < D[i-1][j][t][1] ? D[i-1][j][t-1][0]+col[i][j] : D[i-1][j][t][1]+col[i][j];
                }
            }
        }
        bool ispossible = false;
        int range = N < M ? N*2 : M*2;
        for(int t = 0; t <= range; t++){
            if(D[M-1][N-1][t][0] <= G || D[M-1][N-1][t][1] <= G){
                ispossible = true;
                printf("%d\n", L*(N+M-2)+t);
                break;
            }
        }
        if(!ispossible)
            printf("-1\n");
    }
}
