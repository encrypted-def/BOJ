#include <stdio.h>
#include <algorithm>
#include <queue>
using namespace std;
typedef pair<int, int> PAIR;
typedef pair<PAIR, bool> PAIR_kind; // true : beaver's move, false : water's move
#define X first
#define Y second
int dx[4] = { 1, -1, 0, 0 };
int dy[4] = { 0, 0, 1, -1 };
bool isInBounds(int a, int b, int R, int C) {
    if (a < 0 || a >= R)
        return false;
    if (b < 0 || b >= C)
        return false;
    return true;
}
int main(void) {
    int R, C;
    scanf("%d %d", &R, &C);
    char map[52][52];
    int depth[53][53]; // -3 : destination, -2 : impossible to move, -1 : unvisited
    for (int i = 0; i < R; i++)
        scanf("%s", map[i]);
    queue<PAIR_kind> Q;
    int S_i, S_j;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (map[i][j] == 'D')
                depth[i][j] = -3;
            else if (map[i][j] == '*') {
                depth[i][j] = 0;
                Q.push({ {i,j}, false });
            }
            else if (map[i][j] == 'S') {
                depth[i][j] = 0;
                S_i = i; S_j = j; // 시작 장소를 큐의 맨 뒤에 넣기 위해 지금 바로 큐에 담지는 않음
            }
            else if (map[i][j] == 'X')
                depth[i][j] = -2;
            else
                depth[i][j] = -1;
        }
    }
    Q.push({ { S_i, S_j }, true });
    while (!Q.empty()) {
        PAIR_kind cur = Q.front();
        Q.pop();
        int x = cur.first.first;
        int y = cur.first.second;
        bool isBeaver = cur.second;
        for (int dir = 0; dir < 4; dir++) {
            int test_x = x + dx[dir];
            int test_y = y + dy[dir];
            if (!isInBounds(test_x, test_y, R, C))
                continue;
            if (depth[test_x][test_y] == -3) {
                if (isBeaver) { // 고슴도치가 Destination에 닿은거라면
                    printf("%d\n", depth[x][y] + 1);
                    return 0;
                }
                // 물이 닿은거라면 물은 굴을 침범할 수 없으니 그냥 무시하면 됨
            }
            else if (depth[test_x][test_y] == -1) { // 아직 {test_x, test_y}에 방문한적이 없다면
                depth[test_x][test_y] = depth[x][y] + 1;
                Q.push({ {test_x, test_y}, isBeaver });
            }
            else // 방문했거나 unreachable
                continue;
        }
    }
    // while문을 탈출했다는 것은 고슴도치가 destination에 갈 수 없다는 뜻
    printf("KAKTUS");
    return 0;
}
