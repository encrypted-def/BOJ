#include <stdio.h>
#include <algorithm>
#include <queue>
#define X first
#define Y second
using namespace std;
typedef pair<int, int> PAIR;
 
bool isValid(PAIR tmp, int l) {
    if (tmp.X < 0 || tmp.X >= l || tmp.Y < 0 || tmp.Y >= l)
        return false;
    return true;
}
int calculate(int l, int x1, int y1, int x2, int y2) {
    int depth[302][302] = { 0, }; // isvisit의 역할도 겸하기 위해 원래 depth에 1을 더한 채로 가지고 있을 것임
    depth[x1][y1] = 1;
    queue<PAIR> Q;
    int dx[8] = { -2, -1, 1, 2, 2, 1, -1, -2 };
    int dy[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };
    Q.push(make_pair(x1, y1));
    while (!Q.empty()) {
        PAIR current = Q.front();
        Q.pop();
        for (int dir = 0; dir < 8; dir++) {
            PAIR candidate = make_pair(current.X + dx[dir], current.Y + dy[dir]);
            if (!isValid(candidate, l) || depth[candidate.X][candidate.Y] > 0) // 판을 벗어났거나 이미 방문한 곳이면
                continue;
            Q.push(candidate);
            depth[candidate.X][candidate.Y] = depth[current.X][current.Y] + 1;
            if (candidate == make_pair(x2, y2))
                return depth[candidate.X][candidate.Y] - 1;
        }
    }
    return -1;
}
int main(void) {
    int n;
    scanf("%d", &n);
    while (n--) {
        int l, x1, y1, x2, y2;
        scanf("%d %d %d %d %d", &l, &x1, &y1, &x2, &y2);
        if (x1 == x2 && y1 == y2) {
            printf("0\n");
            continue;
        }
        printf("%d\n", calculate(l, x1, y1, x2, y2));
    }
 
}
