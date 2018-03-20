#include <stdio.h>
int N;
int num[103];
long long D[100][21];
int main(void) {
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%d", &num[i]);
	D[0][num[0]] = 1;
	for (int i = 1; i < N-1; i++) {
		for (int j = 0; j <= 20 - num[i]; j++)
			D[i][j] += D[i-1][j + num[i]];
		for (int j = num[i]; j <= 20; j++)
			D[i][j] += D[i-1][j - num[i]];
	}
	printf("%lld", D[N - 2][num[N - 1]]);
}
