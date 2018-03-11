#include <stdio.h>
#include <algorithm>
#include <vector>
using namespace std;
int N, M, K;
char lamp[51][51];
int D[51];
int main(void) {
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++)
		scanf("%s", lamp[i]);	
	scanf("%d", &K);
	vector<long long> V;
	for (int i = 0; i < N; i++) {
		long long val = 0;
		int num0 = 0;
		for (int j = 0; j < M; j++) {
			val = 2 * val + (lamp[i][j] - '0');
			num0 += (lamp[i][j] == '0');
		}
		if (num0 > K || (K - num0) % 2 != 0)
			continue;
		V.push_back(val);
	}
	sort(V.begin(), V.end());
	if (V.empty()) {
		printf("0");
		return 0;
	}
	D[0] = 1;
	int mx = 1;

	for (int i = 1; i < V.size(); i++) {
		if (V[i] == V[i - 1]) {
			D[i] = D[i - 1] + 1;
			mx = max(mx, D[i]);
		}
		else
			D[i] = 1;
	}
	printf("%d", mx);
}
