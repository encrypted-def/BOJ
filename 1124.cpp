#include <stdio.h>
int D[100003];
bool isPrime[100003];
int main(void) {
	D[1] = false;
	for (int i = 2; i <= 100003; i++) {
		isPrime[i] = true;
		for (int d = 2; d*d <= i; d++) {
			if (i % d == 0) {
				D[i] = D[i / d] + 1;
				isPrime[i] = false;
				break;
			}
		}
		if (isPrime[i])
			D[i] = 1;
	}
	int A, B;
	scanf("%d %d", &A, &B);
	int sum = 0;
	for (int i = A; i <= B; i++)
		sum += isPrime[D[i]];
	printf("%d", sum);
}
