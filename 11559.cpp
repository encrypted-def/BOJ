#include <stdio.h>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;
typedef pair<int, int> PAIR;
const int N = 12;
const int M = 6;
const int dx[4] = { 1,-1,0,0 };
const int dy[4] = { 0,0,1,-1 };
char field[N][M+1];
#define X first
#define Y second
bool IsOutOfBounds(int x, int y) {
	return x < 0 || x >= N || y < 0 || y >= M;
}
int main(void) {
	for (int i = 0; i < N; i++)
		scanf("%s", field[i]);
	bool isLeft = true; // 아직 터트릴 것이 남았는지 체크
	int ans = -1; // 연쇄 갯수
	while (isLeft) {
		ans++;
		isLeft = false;
		int area[N][M];
		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++)
				area[i][j] = -1; // 방문했으면 -1이 아닌 다른 양수가 들어감
		int color = 1;
		vector<int> boom;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (field[i][j] == '.' || area[i][j] > 0)
					continue;
				area[i][j] = color;
				stack<PAIR> S;
				S.push({ i,j });
				int area_num = 1;
				while (!S.empty()) {
					PAIR cur = S.top();
					S.pop();
					for (int dir = 0; dir < 4; dir++) {
						int x = cur.X + dx[dir];
						int y = cur.Y + dy[dir];
						if (IsOutOfBounds(x, y) || field[x][y] != field[cur.X][cur.Y] || area[x][y] > 0)
							continue;
						area_num++;
						area[x][y] = area[cur.X][cur.Y];
						S.push({ x,y });
					}
				}
				if (area_num >= 4) {
					isLeft = true;
					boom.push_back(color);
				}
				color++;
			}
		}
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (find(boom.begin(), boom.end(), area[i][j]) != boom.end())
					field[i][j] = '.';
			}
		} // 4개 이상 붙어있는 뿌요를 제거
		for (int col = 0; col < 6; col++) {
			int floor_idx = 11;
			for (int row = 11; row >= 0; row--) {
				if (field[row][col] != '.') {
					char tmp = field[row][col];
					field[row][col] = '.';
					field[floor_idx--][col] = tmp;
				}
			}
		}
	}
	printf("%d", ans);
}
