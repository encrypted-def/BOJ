#include <stdio.h>
#include <vector>
using namespace std;
typedef long long ll;
ll D[52][130]; // D[i][j] : 시작 상태가 + (j + 60)일 때 길이 i이면서 괄호ㄴㄴ문자열인 갯수. 음수때문에 + 60을 해서 처리함
int main(void) {
	for (int i = 1; i <= 120; i++) {
		D[1][i] = 2;
		D[0][i] = 1;
	}
	D[0][60] = 0;
	D[1][61] = 1;
	for (int i = 2; i <= 50; i++) {
		for (int j = 1; j < 60; j++)
			D[i][j] = (1ll << i);
		for (int j = 60; j <= 120; j++)
			D[i][j] = D[i - 1][j - 1] + D[i - 1][j + 1];
	}
	ll N, K;
	scanf("%lld %lld", &N, &K);
	if (N % 2 == 0 && K >= D[N][60]) { // K이 괄호ㄴㄴ수 갯수보다 많은 경우
		printf("-1");
		return 0;
	}
	ll cnt = 0; // 현재 prefix보다 사전순으로 빠른 것들의 갯수
	bool isFail = false; // 올바른 괄호쌍이 될 여지가 없으면 true
	int prefix_score = 60; // (가 있으면 +1, )가 있으면 -1
	for (int i = 1; i <= N; i++) {
		ll cmp_val = D[N - i][prefix_score+1]; // '('를 배치했을 때 추가되는 갯수
		if (isFail)
			cmp_val = 1ll << (N - i);
		if (cnt + cmp_val > K) {
			prefix_score++;
			printf("(");
		}
		else {
			cnt += cmp_val;
			prefix_score--;
			printf(")");
		}
		if (prefix_score < 60) isFail = true;
	}
	return 0;
}
