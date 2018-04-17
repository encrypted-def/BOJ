#include <stdio.h>
#include <deque>
#include <algorithm>
using namespace std;
#define X first
#define Y second
typedef pair<int, int> pii;
int main(void) {
	int N, L;
	scanf("%d %d", &N, &L);
	deque<pii> DQ;
	for (int i = 0; i < N; i++) {
		int t;
		scanf("%d", &t);
		while (!DQ.empty() && DQ.back().X > t)
			DQ.pop_back();
		DQ.push_back({ t,i });
		while (i - DQ.front().Y >= L)
			DQ.pop_front();
		printf("%d ", DQ.front().X);
	}
}
