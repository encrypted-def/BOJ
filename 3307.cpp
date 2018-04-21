#include <stdio.h>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <functional>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };
#define X first
#define Y second
int n;
int x[200003];
int r[200003];
double ans[200003];
double max_radius(double d, double r) {
	return 0.25*d*d / r;
}
vector<int> v; // 반지름 작아지고 오른쪽으로 가는 순으로 저장
int main(void) {
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d %d", &x[i], &r[i]);
	ans[0] = r[0];
	v.push_back(0);
	for (int i = 1; i < n; i++) {
		ans[i] = r[i];
		while (!v.empty()) {
			double rr = max_radius((double)x[i] - x[v.back()], ans[v.back()]);

			ans[i] = min(rr, ans[i]);
			if (ans[i] > ans[v.back()]-1e-10)
				v.pop_back();
			else
				break;
		}
		v.push_back(i);
	}
	for (int i = 0; i < n; i++)
		printf("%.10f\n", ans[i]);
}
