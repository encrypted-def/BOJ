#include <stdio.h>
#include <algorithm>
using namespace std;
int m[100003];
int N, M;
int calc(int limit) {
	int ans = 1;
	int now = 0;
	for (int i = 0; i < N; i++) {
		if (now + m[i] > limit) {
			ans++;
			now = m[i];
		}
		else
			now += m[i];
	}
	return ans;
}
int main(void) {
	scanf("%d %d", &N, &M);
	int st = 1;
	int en = 1000000000;
	for (int i = 0; i < N; i++) {
		scanf("%d", &m[i]);
		st = max(st, m[i]);
	}
	while (st < en) {
		int mid = (st + en) / 2;
		if (calc(mid) > M)
			st = mid + 1;
		else
			en = mid;
	}
	printf("%d", st);
}
