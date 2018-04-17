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
int L;
int pt[1000003];
ll val[1000003];
int main(void) {
	scanf("%d", &L);
	for (int i = 1; i <= L; i++)
		scanf("%d", &pt[i]);
	for (int d = 1; d <= L; d++) 
		for (int i = d; i <= L; i += d)
			val[d] += pt[i];
	ll mx = 1;
	for (int d = 1; d <= L; d++)
		if (val[mx] < val[d])
			mx = d;
	if (val[mx] <= 0) {
		printf("0 0");
		return 0;
	}
	printf("%lld %lld", mx, val[mx]);
}
