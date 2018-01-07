#include <stdio.h>
int main(void) {
	int T;
	scanf("%d", &T);
	while (T--) {
		int a;
		scanf("%d", &a);
		if (6 % a == 0)
			printf("0\n");
		else if (a == 4)
			printf("2\n");
		else
			printf("1\n");
	}
}
