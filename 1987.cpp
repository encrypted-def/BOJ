#include <stdio.h>
#include <algorithm>
using namespace std;
int R, C;
char board[21][21];
int isvisited[26];
int maxdepth = 0;
int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1, -1, 0,0 };
void dfs(int r, int c, int depth) {
    maxdepth = max(maxdepth, depth);
    isvisited[board[r][c] - 'A'] = true;
    for (int dir = 0; dir < 4; dir++) {
        if (r + dx[dir] < 0 || r + dx[dir] >= R || c+dy[dir] < 0 || c+dy[dir] >= C)
            continue;
        if (isvisited[board[r + dx[dir]][c + dy[dir]] - 'A'])
            continue;
        dfs(r + dx[dir], c + dy[dir], depth + 1);
    }
    isvisited[board[r][c] - 'A'] = false;
}
int main(void) {
    scanf("%d %d", &R, &C);
    for (int i = 0; i < R; i++)
        scanf("%s", board[i]);
    dfs(0, 0, 1);
    printf("%d", maxdepth);
}
