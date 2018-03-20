#include <stdio.h>
#include <algorithm>
using namespace std;
int N;
int A[2005];
int B[2005];
int D[2005][2005];
int main(void) {
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%d", &A[i]);
	for (int i = 0; i < N; i++)
		scanf("%d", &B[i]);
	for (int i = N-1; i >= 0; i--) {
		for (int j = N-1; j >= 0; j--) {
			if (i != N-1)
				D[i][j] = max(D[i][j], D[i + 1][j]);
			if (i != N-1 && j != N-1)
				D[i][j] = max(D[i][j], D[i + 1][j + 1]);
			if (A[i] > B[j]) {
				if (j != N-1)
					D[i][j] = max(D[i][j], D[i][j + 1] + B[j]);
				else
					D[i][j] = max(D[i][j], B[j]);
			}
		}
	}
	printf("%d", D[0][0]);
	return 0;
}
