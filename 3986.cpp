#include <stdio.h>
#include <string.h>
#include <stack>
using namespace std;
int main(void) {
	int N;
	int cnt = 0;
	scanf("%d", &N);
	while (N--) {
		char word[100005];
		scanf("%s", word);
		int len = strlen(word);
		stack<char> S;
		for (int i = 0; i < len; i++) {
			if (S.empty() || S.top() != word[i])
				S.push(word[i]);
			else
				S.pop();
		}
		cnt += S.empty();
	}
	printf("%d", cnt);
}
