#include <stdio.h>
#include <algorithm>
using namespace std;
int main(void) {
    int n;
    scanf("%d", &n);
    int mindiv = 0x7fffffff;
    int maxdiv = -1;
    while (n--) {
        int t;
        scanf("%d", &t);
        mindiv = min(mindiv, t);
        maxdiv = max(maxdiv, t);
    }
    printf("%lld", 1LL * mindiv * maxdiv);
}
