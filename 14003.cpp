#include <stdio.h>
#include <algorithm>
#include <vector>
using namespace std;
int A[1000001];
int LIS[1000001];
int N;
int myLIS[1000001];
int main(void) {
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%d", &A[i]);
	LIS[0] = A[0];
	myLIS[0] = 1;
	int len = 1;
	for (int i = 0; i < N; i++) {
		if (A[i] > LIS[len - 1]) {
			LIS[len++] = A[i];
			myLIS[i] = len;
			continue;
		}
		int idx = lower_bound(LIS, LIS + len, A[i]) - LIS;
		LIS[idx] = A[i];
		myLIS[i] = idx + 1;
	}
	printf("%d\n", len);

	vector<int> V;
	for (int i = N - 1; i >= 0; i--) {
		if (myLIS[i] == len) {
			V.push_back(A[i]);
			len--;
		}
	}
	reverse(V.begin(), V.end());
	for (auto v : V)
		printf("%d ", v);
		
}
