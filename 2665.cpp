#include <stdio.h>
#include <algorithm>
#include <queue>
#include <functional>
using namespace std;
typedef pair<int, int> PAIR;
typedef pair<int, PAIR> PQ_element;
#define X first
#define Y second
#define INF 1e9
int n;
char map[52][52];
int dist[52][52]; // (0,0)으로부터의 거리
int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };
bool isInBounds(int x, int y) {
    return (0 <= x) && (x < n) && (0 <= y) && (y < n);
}
int main(void) {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%s", map[i]);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            dist[i][j] = INF;
    }
    dist[0][0] = 0;
    bool isVisited[52][52] = { false, };
    priority_queue<PQ_element, vector<PQ_element>, greater<PQ_element>> PQ;
    PQ.push({ 0,{0,0} });
    while (!PQ.empty()) {
        PAIR cur;
        do {
            cur = PQ.top().second;
            PQ.pop();
        } while (!PQ.empty() && isVisited[cur.X][cur.Y]);
        if (isVisited[cur.X][cur.Y])
            break;
        isVisited[cur.X][cur.Y] = true;
        for (int dir = 0; dir < 4; dir++) {
            int newX = cur.X + dx[dir];
            int newY = cur.Y + dy[dir];
            if (!isInBounds(newX, newY))
                continue;
            if (dist[newX][newY] > dist[cur.X][cur.Y] + (map[newX][newY] == '0')) {
                dist[newX][newY] = dist[cur.X][cur.Y] + (map[newX][newY] == '0');
                PQ.push({ dist[newX][newY], {newX, newY} });
            }
        }
    }
    printf("%d", dist[n - 1][n - 1]);
}
