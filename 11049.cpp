#include <stdio.h>
#include <algorithm>
using namespace std;
int N;
int D[501][501];
int arr[501][2];
int main(void) {
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%d%d", &arr[i][0], &arr[i][1]);
	for (int len = 2; len <= N; len++) {
		for (int st = 0; st <= N - len; st++) {
			D[st][st + len] = 0x7fffffff;
			for(int sep = st+1; sep < st+len; sep++)	
				D[st][st + len] = min(D[st][st+len], D[st][sep] + D[sep][st + len] + arr[st][0] * arr[sep][0] * arr[st + len - 1][1]);
		}
	}
		printf("%d", D[0][N]);
}
