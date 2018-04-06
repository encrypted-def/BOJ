#include <stdio.h>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <functional>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define X first
#define Y second
vector<int> affect[9] = { {0,1,3,4},{0,1,2},{1,2,4,5},{0,3,6},{1,3,4,5,7},{2,5,8},{3,4,6,7},{6,7,8},{4,5,7,8} };
pii D[300000]; // {이전 값, Move}
int pow4(int n) {
	return 1 << (2*n);
}
void v2i(vector<int>& V, int* val) {
	*val = 0;
	for (int i = 0; i < 9; i++)
		(*val) += pow4(8-i)*V[i];
}
void i2v(vector<int>& V, int val) {
	V.resize(9);
	for (int i = 8; i >= 0; i--) {
		V[i] = val % 4;
		val /= 4;
	}
}
int main(void) {
	for (int i = 0; i < 300000; i++)
		D[i] = { -2,-2 };
	vector<int> state(9);
	int init = 0;
	for (int i = 0; i < 9; i++)
		scanf("%d", &state[i]);
	v2i(state, &init);
	D[init] = { -1, -1 };
	queue<int> Q;
	Q.push(init);
	while (true) {
		int cur = Q.front();
		Q.pop();
		vector<int> curV;
		i2v(curV, cur);
		for (int i = 0; i < 9; i++) {
			for (auto t : affect[i])
				curV[t] = (curV[t] + 1) % 4;
			int val;
			v2i(curV, &val);
			if (D[val].X != -2) {
				for (auto t : affect[i])
					curV[t] = (curV[t] + 3) % 4;
				continue;
			}
			Q.push(val);
			D[val] = { cur, i + 1 };
			for (auto t : affect[i])
				curV[t] = (curV[t] + 3) % 4;
		}
		if (D[0].X != -2)
			break;
	}
	vector<int> ans;
	int st = 0;
	while (D[st].Y != -1) {
		ans.push_back(D[st].Y);
		st = D[st].X;
	}
	sort(ans.begin(), ans.end());
	for (auto i : ans)
		printf("%d ", i);
}
