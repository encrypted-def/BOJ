#include <stdio.h>
#include <algorithm>
using namespace std;
int N;
int rk[500003];
int main(void) {
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%d", &rk[i]);
	sort(rk, rk + N);
	long long tot = 0;
	for (int i = 0; i < N; i++)
		tot += abs(rk[i] - i - 1);
	printf("%lld", tot);
}
