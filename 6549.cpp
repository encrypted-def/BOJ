#include <stdio.h>
#include <algorithm>
#include <stack>
#define X first
#define Y second
using namespace std;
typedef pair<int, int> PAIR; // height, index
int n;
int h[100004];
int main(void) {
	while (true) {
		scanf("%d", &n);
		if (n == 0)
			break;
		for (int i = 0; i < n; i++)
			scanf("%d", &h[i]);
		stack<PAIR> S;
		long long ans = 0;
		for (int i = 0; i < n; i++) {
			int idx = i;
			while (!S.empty() && S.top().X >= h[i]) {
				ans = max(ans, 1LL * (i - S.top().Y) * S.top().X);
				idx = S.top().Y;
				S.pop();
			}
			S.push({ h[i], idx });
		}
		while (!S.empty()) {
			ans = max(ans, 1LL * (n - S.top().Y) * S.top().X);
			S.pop();
		}
		printf("%lld\n", ans);
	}
}
