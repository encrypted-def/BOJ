#include <stdio.h>
#include <algorithm>
#include <functional>
using namespace std;
int A[4001], B[4001], C[4001], D[4001];
int mid1[16000001], mid2[16000001];
int main(void) {
	int T;
	scanf("%d", &T);
	for (int i = 0; i < T; i++)
		scanf("%d %d %d %d", &A[i], &B[i], &C[i], &D[i]);
	for (int i = 0; i < T; i++) 
		for (int j = 0; j < T; j++) 
			mid1[i*T + j] = A[i] + B[j];
		
	for (int i = 0; i < T; i++)
		for (int j = 0; j < T; j++)
			mid2[i*T + j] = C[i] + D[j];

	sort(mid2, mid2 + T * T);
	long long cnt = 0;
	for (int i = 0; i < T*T; i++)
		cnt += (upper_bound(mid2, mid2 + T * T, -mid1[i]) - lower_bound(mid2, mid2 + T * T, -mid1[i]));
	printf("%lld", cnt);
}
