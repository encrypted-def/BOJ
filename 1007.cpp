#include <stdio.h>
#include <vector>
#include <math.h>
#include <algorithm>
using namespace std;
typedef long long LL;
typedef pair<LL, LL> PAIR;
#define X first
#define Y second
int main(void) {
    int T;
    scanf("%d", &T);
    PAIR point[30];
    while (T--) {
        int N;
        scanf("%d", &N);
        for (int i = 0; i < N; i++)
            scanf("%lld %lld", &point[i].X, &point[i].Y);
        LL MN = 0x7fffffffffffffffLL;
        vector<int> brute(N);
        fill(brute.begin() + N / 2, brute.end(), 1);
        do {
            PAIR val = { 0LL, 0LL };
            for (int i = 0; i < N; i++) {
                if (brute[i]) {
                    val.X += point[i].X;
                    val.Y += point[i].Y;
                }
                else {
                    val.X -= point[i].X;
                    val.Y -= point[i].Y;
                }
            }
            MN = min(MN, val.X*val.X + val.Y*val.Y);
        } while (next_permutation(brute.begin(), brute.end()));
        printf("%.6f\n", sqrt((double)MN));
    }
}
