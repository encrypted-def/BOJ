#include <stdio.h>
#include <algorithm>
#include <vector>
using namespace std;
typedef pair<int, int> pii;
#define X first
#define Y second
int n;
char s[105];
int D[105][105];
int conn[105][105]; // conn[i][j] : i to j를 처리할 때 i가 무엇과 연결됐는가?
int h[105][105]; // h[i][j] : i to j를 처리할 때 높이가 얼마인가?
int valid[105][105]; // valid[i][j] : i to j에 검은 점이 몇개인가.
const int MX = 0x7f7ff;
vector<pii> ans;
void solve(int st, int en) {
	ans.push_back({ st + 1, conn[st][en] });
	if (conn[st][en] != st + 2)
		solve(st + 1, conn[st][en] - 1);
	if (conn[st][en] != en)
		solve(conn[st][en], en);
}
int main(void) {
	scanf("%d", &n);
	scanf("%s", s);
	for (int i = 0; i < n; i++)
		for (int j = i + 1; j <= n; j++)
			D[i][j] = MX;
	for (int i = 0; i < n; i++) {
		valid[i][i + 1] = s[i] - '0';
		for (int j = i + 2; j <= n; j++)
			valid[i][j] = valid[i][j - 1] + (s[j - 1] - '0');
	}
	for (int sz = 2; sz <= n; sz += 2) {
		for (int i = 0; i <= n - sz; i++) {
			if (valid[i][i+sz] != sz / 2) // 검은 점 흰 점의 갯수가 다르면
				continue;
			if (s[i] + s[i + sz - 1] == '0' + '1') {
				h[i][i + sz] = h[i + 1][i + sz - 1] + 1;
				conn[i][i + sz] = i + sz;
				D[i][i + sz] = 2 * h[i][i + sz] + (sz - 1) + D[i+1][i+sz-1];
			}
			for (int sep = i + 2; sep < i + sz; sep += 2) {				
				if (D[i][i + sz] > D[i][sep] + D[sep][i + sz]) {
					D[i][i + sz] = D[i][sep] + D[sep][i + sz];
					conn[i][i + sz] = sep;
					h[i][i + sz] = max(h[i][sep], h[sep][i + sz]);
				}
			}
		}
	}
	printf("%d\n", D[0][n]);
	solve(0, n);
	sort(ans.begin(), ans.end());
	for (auto t : ans)
		printf("%d %d\n", t.X, t.Y);
}
