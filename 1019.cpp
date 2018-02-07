#include <stdio.h>
int cnt[10];
// prefix = 47, sz = 3 -> 47000~47999
// prefix = 5, sz = 2 -> 500~599
// prefix = 1, sz = 1 -> 10~19
// prefix = 42, sz = 0 -> 42~42
int pow10(int a) {
	int t = 1;
	while (a--) t *= 10;
	return t;
}
void calc(int prefix, int sz) {
	if (prefix == 0) {
		if (sz == 0)
			return;
		for (int i = 0; i < 10; i++)
			cnt[i] += sz * pow10(sz - 1);
		for (int i = 1; i < sz; i++) {
			cnt[0] -= 9 * pow10(sz - 1 - i)*i;
		}
		cnt[0] -= sz;
	}
	else{
		while (prefix) {
			cnt[prefix % 10] += pow10(sz);
			prefix /= 10;
		}
		if (sz == 0)
			return;
		for (int i = 0; i < 10; i++)
			cnt[i] += sz * pow10(sz - 1);
	}
}
int main(void) {
	int N;
	scanf("%d", &N);
	N++;
	int now = 0;
	while (now < N) {
		for (int i = 0; ; i++) {
			if (now + pow10(i) > N) {
				calc(now / pow10(i - 1), i - 1);	
				now += pow10(i - 1);
				break;
			}
		}
	}
	for (int i = 0; i < 10; i++)
		printf("%d ", cnt[i]);
}
