#include <stdio.h>
#include <algorithm>
#include <functional>
using namespace std;
int N;
int lope[100004];
int main(void) {
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%d", &lope[i]);
	sort(lope, lope + N, greater<int>());
	int mx = 0;
	for(int k = 1; k <= N; k++)
		mx = max(mx, lope[k - 1] * k);
	printf("%d", mx);
}
