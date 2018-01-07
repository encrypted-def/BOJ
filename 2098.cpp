#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
int W[20][20];
int D[20][1 << 17];
/*
ex : bitmask = 0001101일 때
0,2,3번마을을 이미 방문한 것임
*/
 
int main(void) {
    int N;
    scanf("%d", &N);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            scanf("%d", &W[i][j]);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < (1 << N); j++)
            D[i][j] = -1;
    D[0][1] = 0;
    for (int bitmask = 2; bitmask < (1 << N); bitmask++) {
        vector<int> VisitedList;
        for (int i = 0; i < N; i++) {
            if ((bitmask & (1 << i)) == (1 << i)) // bitmask의 i-th 값이 1이라면
                VisitedList.push_back(i); // 마지막 방문지가 될 자격이 있음
        }
        for (auto const &cur_city : VisitedList) {
            int tmp = bitmask ^ (1 << cur_city); // bitmask에서 cur_city를 뺀 것
            
            for (int prev_city = 0; prev_city < N; prev_city++) {
                if (D[prev_city][tmp] == -1 || W[prev_city][cur_city] == 0)
                    continue;
                if (D[cur_city][bitmask] == -1)
                    D[cur_city][bitmask] = D[prev_city][tmp] + W[prev_city][cur_city];
                else
                    D[cur_city][bitmask] = min(D[cur_city][bitmask], D[prev_city][tmp] + W[prev_city][cur_city]);
            }
    //        printf("D[%d][%d] : %d\n", cur_city, bitmask, D[cur_city][bitmask]);
        }
    }
    int mn = 0x7fffffff;
    for (int i = 1; i < N; i++) {
        if (D[i][(1 << N) - 1] == -1 || W[i][0] == 0)
            continue;
        mn = min(mn, D[i][(1 << N) - 1] + W[i][0]); // i에서 0으로 최종적으로 이동해야 끝남
    }
    printf("%d", mn);
}
