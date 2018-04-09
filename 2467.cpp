#include <stdio.h>
#include <algorithm>
#include <vector>
using namespace std;
typedef pair<int, int> pii;
#define X first
#define Y second
int N;
int arr[100003];
vector<int> acid;
vector<int> base;
vector<pii> V;
int val1=1000000000, val2=1000000000;
int main(void) {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		int t;
		scanf("%d", &t);
		if (t > 0)
			acid.push_back(t);
		else
			base.push_back(-t);
	}
	sort(acid.begin(), acid.end());
	sort(base.begin(), base.end());
	if (acid.size() >= 2) {
		if (abs(val2 + val1) > acid[0] + acid[1])
			val1 = acid[0], val2 = acid[1];
	}
	if (base.size() >= 2) {
		if (abs(val2 + val1) > abs(base[0] + base[1]))
			val1 = -base[1], val2 = -base[0];
	}
	if (acid.empty() || base.empty()) {
		printf("%d %d", val1, val2);
		return 0;
	}
	for (int a : acid) {
		auto t = lower_bound(base.begin(), base.end(), a);
		if (t != base.begin()) {
			if (abs(val2 + val1) > abs(a - *(t - 1)))
				val1 = -*(t - 1), val2 = a;
		}
		if (t != base.end()) {
			if (abs(val2 + val1) > abs(a - *t))
				val1 = -(*t), val2 = a;
		}
	}
	printf("%d %d", val1, val2);
}
