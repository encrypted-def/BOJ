#include <stdio.h>
#include <algorithm>
#include <vector>
using namespace std;
int N;
int T[17];
int P[17];

int main(void) {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d %d", &T[i], &P[i]);
		T[i]--;
	}
	int mx = 0;
	for (int day = 1; day <= N; day++) {
		vector<bool> V(N);
		fill(V.begin() + (N - day), V.end(), true);
		do {
			int val = 0;
			int last_day = -1;
			for (int i = 0; i < N; i++) {
				if (V[i]) {
					if (last_day >= i) {
						val = -8888;
						break;
					}
					if (T[i] + i >= N) {
						val = -8888;
						break;
					}
					val += P[i];
					last_day = T[i] + i;
				}
			}
			mx = max(mx, val);
		} while (next_permutation(V.begin(),V.end()));
	}
	printf("%d", mx);
}
