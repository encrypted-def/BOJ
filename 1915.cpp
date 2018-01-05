#include <stdio.h>
#include <algorithm>
using namespace std;
char map[1001][1001];
int D[1001][1001]; // D[i][j] : (i, j)를 오른쪽 하단으로 두는 1로 된 가장 큰 직사각형의 변의 길이
int n, m;
 
int min3(int a, int b, int c) {
    return min(min(a, b), c);
}
int main(void) {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++)
        scanf("%s", map[i]);
    int mx = 0;
    for (int i = 0; i < m; i++) 
        D[0][i] = map[0][i] - '0'; // 첫 row만 처리
 
    for(int i = 1; i < n; i++){
        D[i][0] = map[i][0] - '0';
        for (int j = 1; j < m; j++) 
            D[i][j] = (map[i][j] - '0') * (min3(D[i][j - 1], D[i - 1][j], D[i - 1][j - 1]) + 1);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            mx = max(mx, D[i][j]);
    }
    printf("%d", mx*mx);
}
