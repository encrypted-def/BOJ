#include <stdio.h>
#include <vector>
using namespace std;
int main(void) {
    vector<int> F;
    F.push_back(1);
    F.push_back(2);
    int len = 2;
    while (true) {
        int val = F[len - 1] + F[len - 2];
        if (val > 1000000000)
            break;
        F.push_back(val);
        len++;
    }
    int T;
    scanf("%d", &T);
    while (T--) {
        int N;
        scanf("%d", &N);
        
        vector<int> ans;
        int idx = len - 1;
        while (N >= 1) {
            if (N == 1) {
                ans.push_back(1);
                break;
            }
            while (idx >= 0 && F[idx] > N)
                idx--;
            // 이제 F[idx] <= N인 상태
            ans.push_back(F[idx]);
            N -= F[idx];
        }
        for (int i = ans.size() - 1; i >= 0; i--)
            printf("%d ", ans[i]);
        printf("\n");
    }
}
