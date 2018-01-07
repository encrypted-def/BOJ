#include <stdio.h>
int map[103][103]; // map[i][j] : (i, j)칸에 보이는 색종이의 종류
int cnt[103];
int main(void) {
    int N;    
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        int x, y, width, height;
        scanf("%d %d %d %d", &x, &y, &width, &height);
        for (int a = x; a < x + width; a++) {
            for (int b = y; b < y + height; b++)
                map[a][b] = i;
        }
    }
    
    for (int i = 0; i <= 100; i++)
        for (int j = 0; j <= 100; j++)
            cnt[map[i][j]]++;
    for (int i = 1; i <= N; i++)
        printf("%d\n", cnt[i]);
}
