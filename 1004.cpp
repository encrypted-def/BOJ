#include <stdio.h>
bool isInner(int cx, int cy, int r, int x, int y) {
    return r*r > (cx - x)*(cx - x) + (cy - y)*(cy - y);
}
int main(void) {
    int T;
    scanf("%d", &T);
    while (T--) {
        int x1, y1, x2, y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        int n;
        scanf("%d", &n);
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            int cx, cy, r;
            scanf("%d %d %d", &cx, &cy, &r);
            cnt += isInner(cx, cy, r, x1, y1) ^ isInner(cx, cy, r, x2, y2); // 하나는 안에, 하나는 밖에 있을 경우 cnt 1 증가
        }
        printf("%d\n", cnt);
    }
    return 0;
}
