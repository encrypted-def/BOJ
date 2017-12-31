#include <stdio.h>
int min4(int a, int b, int c, int d) {
    int min = a;
    min = min < b ? min : b;
    min = min < c ? min : c;
    min = min < d ? min : d;
    return min;
}
int main(void) {
    int x, y, w, h;
    scanf("%d %d %d %d", &x, &y, &w, &h);
    printf("%d", min4(x, w - x, y, h - y));
}
