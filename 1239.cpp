#include <stdio.h>
#include <algorithm>
#include <vector>
using namespace std;
int calc(vector<int> chart) {
    int len = chart.size();
    int cnt = 0;
    for (int st = 0; st < len; st++) {
        int sum = 0;
        int tmp_idx = st;
        while (sum < 50) {
            sum += chart[tmp_idx];
            tmp_idx = (tmp_idx + 1) % len;
        }
        cnt += (sum == 50);
    }
    return cnt;
}
int main(void) {
    int N;
    scanf("%d", &N);
    vector<int> chart(N);
    for (int i = 0; i < N; i++)
        scanf("%d", &chart[i]);
    sort(chart.begin(), chart.end());
    int mx = 0;
    do {
        mx = max(mx, calc(chart));
    } while (next_permutation(chart.begin(), chart.end()));
    printf("%d", mx / 2);
}
