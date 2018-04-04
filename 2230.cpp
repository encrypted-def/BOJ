#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
int N, M;
int A[100003];
int main(void) {
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++)
		scanf("%d", &A[i]);
	sort(A, A + N);
	int j = 0;
	int diff = 0x7f7f7f7f;
	for (int i = 0; i < N; i++) {
		while (j < N && A[j] - A[i] < M)
			j++;
		if (j == N)
			break;
		diff = min(diff, A[j] - A[i]);
	}
	printf("%d", diff);
}
