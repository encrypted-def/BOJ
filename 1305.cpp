#include <stdio.h>
int L;
char a[1000003];
int f[1000003];
int main(void) {
	scanf("%d", &L);
	scanf("%s", a);
	f[0] = -1;
	for (int i = 1; i < L; i++) {
		int j = f[i - 1];
		while (a[i] != a[j + 1] && j >= 0)
			j = f[j];
		if (a[i] == a[j+1])
			f[i] = j + 1;
		else
			f[i] = -1;
	}
	printf("%d", L - 1 - f[L - 1]);
}
