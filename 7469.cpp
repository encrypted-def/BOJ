#include <stdio.h>
#include <vector>
#include <algorithm>
#define X first
#define Y second
using namespace std;
typedef pair<int, int> PAIR;
int num[100004];
int in[100004];
int shrink[100004];
PAIR t[100004];
int main(void) {
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d", &in[i]);
        t[i].X = in[i];
        t[i].Y = i;
    }
    sort(t, t + n);
    for (int i = 0; i < n; i++) {
        shrink[i] = t[i].X;
        num[t[i].Y] = i;
    }
    while (m--) {
        int i, j, k;
        scanf("%d %d %d", &i, &j, &k);
        vector<int> V(n);
        for (int idx = i-1; idx <= j-1; idx++) {
            V[num[idx]] = 1;
        }
        int cnt = 0;
        for (int idx = 0; idx < n; idx++) {
            if (V[idx])
                cnt++;
            if (cnt == k) {
                printf("%d\n", shrink[idx]);
                break;
            }
        }
    }
}
