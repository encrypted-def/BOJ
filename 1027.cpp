#include <stdio.h>
#include <algorithm>
typedef long long ll;
using namespace std;
int N;
ll h[53];
ll left[53]; // 왼쪽으로 보이는 빌딩의 수
ll right[53]; // 오른쪽으로 보이는 빌딩의 수

int main(void) {
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%lld", &h[i]);
	for (int i = 0; i < N; i++) {
		int highidx = -1;
		for (int l = i - 1; l >= 0; l--) {
			if (highidx == -1) {
				highidx = l;
				left[i]++;
				continue;
			}
			ll x1 = i - l;
			ll y1 = h[i] - h[l]; 
			ll x2 = i - highidx;
			ll y2 = h[i] - h[highidx]; // y1/x1 < y2/x2 여야함
			if (y1*x2 < x1*y2) {
				highidx = l;
				left[i]++;
			}
		}
	}
	for (int i = 0; i < N; i++) {
		int highidx = -1;
		for (int r = i + 1; r < N; r++) {
			if (highidx == -1) {
				highidx = r;
				right[i]++;
				continue;
			}
			ll x1 = r - i;
			ll y1 = h[r] - h[i];
			ll x2 = highidx - i;
			ll y2 = h[highidx] - h[i]; // y1/x1 > y2/x2 여야함
			if (y1*x2 > x1*y2) {
				highidx = r;
				right[i]++;
			}
		}
	}
	ll mx = left[0] + right[0];
	for (int i = 0; i < N; i++)
		mx = max(mx, left[i] + right[i]);
	printf("%lld", mx);
}
