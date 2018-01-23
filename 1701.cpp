#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
char T[5003];
int pi[5003];
int main(void) {
	scanf("%s", T);
	int len = strlen(T);
	int mx = 0;
	for (int i = 0; i < len; i++) { // T[i:]의 pi함수를 계산할 예정
		int k = 0;
		for (int j = 1; j < len - i; j++) {
			while (k > 0 && T[i + j] != T[i + k])
				k = pi[k - 1];
			if (T[i + j] == T[i + k])
				pi[j] = ++k;
			else
				pi[j] = 0;
			mx = max(pi[j], mx);
		}
	}
	printf("%d", mx);
}
