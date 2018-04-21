#include <stdio.h>
int cmp(int a1, int a2, int b1, int b2) { // 음수면 a1/a2 < b1/b2
	return a1 * b2 - a2 * b1;
}

int main(void) {
	int B, C, D, A1, A2, E1, E2;
	scanf("%d %d %d %d %d %d %d", &B, &C, &D, &A1, &A2, &E1, &E2);
	long long cnt = 0;
	for (int C1 = 1; C1 <= 1000000; C1++) {
		if (cmp(A1, A2, C1, C) >= 0)
			continue;
		if (cmp(C1, C, E1, E2) >= 0)
			break;
		cnt += ((E1*D - 1) / E2 - (C1*D) / C) * ((B*C1 - 1) / C - (A1*B) / A2);
	}
	printf("%lld", cnt);
}
