#include <stdio.h>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <functional>
#include <tuple>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, char> pic;
#define X first
#define Y second
int T;
pic D[10000];
void i2t(int a, int* t) {
	for (int i = 3; i >= 0; i--) {
		t[i] = a % 10;
		a /= 10;
	}
}
int t2i(int* t) {
	return 1000 * t[0] + 100 * t[1] + 10 * t[2] + t[3];
}
int main(void) {
	scanf("%d", &T);
	while (T--) {
		int aa, B;
		scanf("%d %d", &aa, &B);
		int A = aa;
		fill(D, D + 10000, make_pair( -1,0 ));
		int a[4], b[4];
		
		for (int i = 3; i >= 0; i--) {
			a[i] = aa% 10;
			aa /= 10;
		}
		D[A] = { 1,0 };
		queue<int> Q;
		Q.push(A);
		while (!Q.empty()) {
			int cur = Q.front();
			Q.pop();
			if (D[cur * 2 % 10000].X == -1) {
				D[cur * 2 % 10000] = { cur,'D' };
				Q.push(cur * 2 % 10000);
			}
			int cur_t[4];
			i2t(cur, cur_t);
			int L = 1000 * cur_t[1] + 100 * cur_t[2] + 10 * cur_t[3] + cur_t[0];
			if (D[L].X == -1) {
				D[L] = { cur,'L' };
				Q.push(L);
			}
			int R = 1000 * cur_t[3] + 100 * cur_t[0] + 10 * cur_t[1] + cur_t[2];
			if (D[R].X == -1) {
				D[R] = { cur,'R' };
				Q.push(R);
			}
			if (D[(cur + 9999) % 10000].X == -1) {
				D[(cur + 9999) % 10000] = { cur,'S' };
				Q.push((cur + 9999) % 10000);
			}
		}
		int cur = B;
		vector<char> ans;
		while (cur != A) {
			ans.push_back(D[cur].Y);
			cur = D[cur].X;
		}
		for (int i = ans.size() - 1; i >= 0; i--)
			printf("%c", ans[i]);
		printf("\n");
	}
}
