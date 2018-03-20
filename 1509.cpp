#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
int D[2503]; // D[i] : s[:i]의 분할 갯수
bool isPalindrome[2503][2503]; // isPalindrome[i][j] : s[i:j]가 palindrome인지
char s[2503];
int len;
int main(void) {
	scanf("%s", s);
	len = strlen(s);
	if (len == 1) {
		printf("1");
		return 0;
	}
	if (len == 2) {
		printf("%d", 1 + (s[0] != s[1]));
		return 0;
	}
	for (int l = 1; l <= len; l++) {
		for (int st = 0; st <= len - l; st++) {
			if (l == 1)
				isPalindrome[st][st + l] = true;
			else if (l == 2)
				isPalindrome[st][st + l] = (s[st] == s[st + 1]);
			else
				isPalindrome[st][st + l] = ((s[st] == s[st + l - 1]) && isPalindrome[st + 1][st + l - 1]);
		}
	}
	D[0] = 0;
	D[1] = 1;
	D[2] = 1 + (s[0] != s[1]);
	for (int i = 3; i <= len; i++) {
		D[i] = 0x7f7f7f7f;
		for (int j = i - 1; j >= 0; j--) {
			if(isPalindrome[j][i])
				D[i] = min(D[i], D[j] + 1);
		}
	}
	printf("%d", D[len]);
}
