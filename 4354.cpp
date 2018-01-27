#include <stdio.h>
#include <string.h>

char S[1000004];
int f[1000004];
int main(void) {
	while (true) {
		scanf("%s", S);
		int len = strlen(S);
		if (len == 1 && S[0] == '.')
			break;
		int j = 0;
		for (int i = 1; i < len; i++) {
			while (j > 0 && S[i] != S[j])
				j = f[j - 1];
			if (S[i] == S[j])
				f[i] = ++j;
			else
				f[i] = 0;
		}
		if (f[len - 1] == 0) {
			printf("1\n");
			continue;
		}
		int k = len - f[len - 1];
		if (len % k == 0)
			printf("%d\n", len / k);
		else
			printf("1\n");
	}
}
