#include <stdio.h>
#include <algorithm>
using namespace std;
// nCm = n! / m!*(n-m)!
int amount2(int a) { // a!의 2의 갯수
    int val = a;
    int cnt = 0;
    while (val > 0) {
        val /= 2;
        cnt += val;
    }
    return cnt;
}
int amount5(int a) { // a!의 5의 갯수
    int val = a;
    int cnt = 0;
    while (val > 0) {
        val /= 5;
        cnt += val;
    }
    return cnt;
}
int main(void) {
    int n, m;
    scanf("%d %d", &n, &m);
    int num2 = amount2(n) - amount2(m) - amount2(n - m);
    int num5 = amount5(n) - amount5(m) - amount5(n - m);
    printf("%d", min(num2, num5));
}
