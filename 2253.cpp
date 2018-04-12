#include <stdio.h>
#include <algorithm>
using namespace std;
int D[10003][203];
int N, M;
int block[10003];
int main(void) {
	scanf("%d %d", &N, &M);
	while (M--) {
		int t;
		scanf("%d", &t);
		block[t] = 1;
	}
	for (int i = 0; i <= 10000; i++)
		for (int j = 0; j <= 200; j++)
			D[i][j] = 0x7f7f7f;	
	D[1][0] = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 0; j <= 200; j++) {
			if (D[i][j] == 0x7f7f7f)
				continue;
			for (int jmp = j - 1; jmp <= j + 1; jmp++) {
				if (jmp <= 0 || i + jmp > N || block[i+jmp])
					continue;
				D[i + jmp][jmp] = min(0x7f7f7f, D[i][j] + 1);
			}
		}
	}
	int ans = 0x7f7f7f;
	for (int j = 0; j <= 200; j++)
		ans = min(ans, D[N][j]);
	if (ans == 0x7f7f7f)
		ans = -1;
	printf("%d", ans);
}
