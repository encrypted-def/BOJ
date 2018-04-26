#include <stdio.h>
int N;
char S[2000004];
char P[1000004];
int f[1000004];
int gcd(int a, int b) {
	if (a == 0)
		return b;
	return gcd(b%a, a);
}
int main(void) {
	scanf("%d", &N);
	getchar();
	for (int i = 0; i < N; i++) {
		scanf(" %c", &S[i]);
		S[N+i] = S[i];
	}
	S[2 * N -1] = 0;
	for (int i = 0; i < N; i++)
		scanf(" %c", &P[i]);
	f[0] = -1;
	for (int i = 1; i < N; i++) {
		int j = f[i - 1];
		while (j >= 0 && P[i] != P[j+1])
			j = f[j];
		if (P[i] == P[j + 1])
			f[i] = j + 1;
		else
			f[i] = -1;
	}
	int i = 0, j = 0;
	int cnt = 0;
	while (i < 2*N - 1) {
		if (S[i] == P[j]) {
			i++; j++;
		}
		else if (j == 0) i++;
		else j = f[j - 1] + 1;
		if (j == N) {
			cnt++;
			j = f[j - 1] + 1;
		}
	}
	// cnt/N
	int g = gcd(cnt, N);
	printf("%d/%d", cnt/g, N/g);
}
