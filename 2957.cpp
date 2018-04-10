#include <stdio.h>
#include <map>
#include <algorithm>
using namespace std;
int N;
long long cnt = 0;
int main(void) {
	scanf("%d", &N);
	map<int, int> M;
	int val;
	scanf("%d", &val);
	M[val] = 0;
	printf("0\n");
	for (int i = 1; i < N; i++) {
		int val;
		scanf("%d", &val);
		auto it = M.lower_bound(val);
		int cmp1 = 0;
		int cmp2 = 0;
		if (it != M.end())
			cmp1 = it->second;
		if (it != M.begin()) {
			it--;
			cmp2 = it->second;
		}
		M[val] = max(cmp1, cmp2)+1;
		cnt += max(cmp1, cmp2)+1;
		printf("%lld\n", cnt);
	}
}
