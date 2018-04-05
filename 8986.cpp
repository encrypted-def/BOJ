#include <stdio.h>
#include <algorithm>
using namespace std;
int N;
int x[100004];
long long dist(long long d) {
	long long val = 0;
	for (int i = 0; i < N; i++)
		val += abs(d*i - x[i]);
	return val;
}
int main(void) {
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%d", &x[i]);
	long long st = 1;
	long long en = 1000000000;
	while (en - st > 10) {
		long long mid1 = (st * 2 + en) / 3;
		long long mid2 = (st + en * 2) / 3;
		long long dist1 = dist(mid1);
		long long dist2 = dist(mid2);
		if (dist1 == dist2) {
			st = mid1;
			en = mid2;
		}
		else if (dist1 > dist2)
			st = mid1;
		else
			en = mid2;
	}
	long long mn = 0x7f7f7f7f7f7f7f7f;
	for (long long i = st; i <= en; i++)
		mn = min(mn, dist(i));
	printf("%lld", mn);
}
