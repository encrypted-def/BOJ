#include <stdio.h>
#include <algorithm>
#include <functional>
using namespace std;
typedef pair<int, int> PAIR;
#define X first
#define Y second
int main(void) {
	int T;
	scanf("%d", &T);
	while (T--) {
		int n;
		scanf("%d", &n);
		int cnt[503]; // cnt[i] : 팀 i보다 등수가 높은 팀의 수
		int lastrank[503]; // lastrank[i] : 팀 i의 작년의 순위
		for (int i = 0; i < n; i++) {
			int num;
			scanf("%d", &num);
			cnt[num] = i; // 팀 num이 i+1등이므로 i개의 팀이 팀 i보다 등수가 높다.
			lastrank[num] = i + 1;
		}
		int m;
		scanf("%d", &m);
		while (m--) {
			int a, b;
			scanf("%d %d", &a, &b);
			if (lastrank[a] < lastrank[b]) { // a의 순위가 b보다 더 좋을 경우
				cnt[a]++; // 팀 a보다 등수가 높지 않던 팀 b가 높아졌으므로
				cnt[b]--;
			}
			else {
				cnt[a]--;
				cnt[b]++;
			}
		}
		PAIR tmp[503];
		for (int i = 1; i <= n; i++) {
			tmp[i - 1] = { cnt[i], i };
		}
		sort(tmp, tmp + n);
		bool isPossible = true;
		for (int i = 0; i < n; i++) {
			if (tmp[i].X != i) { // i+1등한 팀에서 그 팀보다 등수가 높은 팀의 수가 i가 아니라면
				isPossible = false;
				break;
			}
		}
		if (!isPossible) {
			printf("IMPOSSIBLE\n");
			continue;
		}
		for(int i = 0; i < n; i++)
			printf("%d ", tmp[i].Y);
		printf("\n");
	}
}
