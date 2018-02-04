#include <stdio.h>
#include <algorithm>
using namespace std;
typedef long long ll;
ll N, K;
ll order(ll val) { // val와 같거나 작은 수가 몇 개가 있는지
	ll sum = 0;
	for (int i = 1; i <= N; i++) {
		sum += min(N, val / i);
		if (i > val)
			break;
	}
	return sum;
}
int main(void) {

	scanf("%lld %lld", &N, &K);
	// order(i) < K을 만족하는 가장 큰 i를 찾고 i+1을 출력하면 된다.
	ll left = 0; 
	ll right = N*N;
	// i는 left~right에 존재
	while (right != left) {
		ll mid = (left + right) / 2 + 1;
		if (order(mid) >= K) {
			right = mid - 1;
		}
		else {
			left = mid;
		}
	}
	printf("%lld", left+1);
}
