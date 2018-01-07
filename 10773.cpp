#include <stdio.h>
#include <stack>
using namespace std;
int main(void) {
    int K;
    scanf("%d", &K);
    stack<int> S;
    while (K--) {
        int t;
        scanf("%d", &t);
        if (t > 0)
            S.push(t);
        else
            S.pop();
    }
    long long sum = 0;
    while (!S.empty()) {
        sum += S.top();
        S.pop();
    }
    printf("%lld", sum);
}
