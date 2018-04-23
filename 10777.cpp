#include <stdio.h>
#include <algorithm>
#include <functional>
using namespace std;
int N, M;
int A[3002];
int B[102];
const int MOD = 5;
int D[10][102][102][3]; // D[i][j][k][0 or 1] : i개의 A, j개의 큰 B, k개의 작은 B, 마지막으로 챙긴 과자가 A이면 0, B이면 1

int main(void) {
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%d", &A[i]);
	scanf("%d", &M);
	for (int j = 0; j < M; j++)
		scanf("%d", &B[j]);
	sort(B, B + M, greater<int>());
	int mx = A[0];	
	for (int i = 0; i <= N; i++) {
		for (int j = 0; j <= M; j++) {
			for (int k = 0; k <= M - j; k++) {
				if (i != 0) {
					D[i%MOD][j][k][0] = A[i - 1];
					int f1[5][4] = { { i - 2,j,k,1 },{ i - 1,j,k - 1,1 },{ i - 2,j,k,0 },{ i - 1,j,k - 1,0 },{i - 1,j,k,2} };
					for (int idx = 0; idx < 5; idx++) {
						if (f1[idx][0] < 0 || f1[idx][1] < 0 || f1[idx][2] < 0) continue;
						D[i%MOD][j][k][0] = max(D[i%MOD][j][k][0], D[f1[idx][0] % MOD][f1[idx][1]][f1[idx][2]][f1[idx][3]] + A[i - 1]);
					}
					mx = max(mx, D[i%MOD][j][k][0]);
				}
				if (j != 0) {
					D[i%MOD][j][k][1] = B[j-1];
					int f2[5][4] = { { i - 1,j - 1,k,1 },{ i,j - 1,k - 1,1 },{ i - 1,j - 1,k,0 },{ i,j - 1,k - 1,0 }, {i,j - 1,k,2} };
					for (int idx = 0; idx < 5; idx++) {
						if (f2[idx][0] < 0 || f2[idx][1] < 0 || f2[idx][2] < 0) continue;
						D[i%MOD][j][k][1] = max(D[i%MOD][j][k][1], D[f2[idx][0] % MOD][f2[idx][1]][f2[idx][2]][f2[idx][3]] + B[j-1]);
					}
					mx = max(mx, D[i%MOD][j][k][1]);
				}
				D[i%MOD][j][k][2] = 0;
				int f3[4][4] = { {i,j - 1,k,1},{i - 1,j,k,0},{ i,j - 1,k,2},{ i - 1,j,k,2 } };
				for (int idx = 0; idx < 4; idx++) {
					if (f3[idx][0] < 0 || f3[idx][1] < 0 || f3[idx][2] < 0) continue;
					D[i%MOD][j][k][2] = max(D[i%MOD][j][k][2], D[f3[idx][0] % MOD][f3[idx][1]][f3[idx][2]][f3[idx][3]]);
				}
			}
		}
	}
	printf("%d", mx);
}
