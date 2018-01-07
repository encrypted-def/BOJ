#include <stdio.h>
#include <algorithm>
using namespace std;
typedef pair<int, int> PAIR;
#define X first
#define Y second
int N;
PAIR building[10005];
int D[10005]; // D[i] : 0번째부터 i번째 건물까지 연결하는 설치비용의 최솟값
int max3(int a, int b, int c) {
    return max(max(a, b), c);
}
int main(void) {    
    scanf("%d", &N);
    for(int i = 0; i < N; i++){
        scanf("%d %d", &building[i].X, &building[i].Y);
        if (building[i].Y < 0)
            building[i].Y = -building[i].Y;
    }
    sort(building, building + N);
    D[0] = building[0].Y * 2;
    for (int i = 1; i < N; i++) {
        int mx_height = building[i].Y;
        D[i] = D[i - 1] + building[i].Y * 2;
        for (int j = i-1; j >= 0; j--) { // j~i번째 건물까지 한 기지국으로 연결할 때 최솟값을 계산해서 D[i]를 갱신할 예정
            mx_height = max(mx_height, building[j].Y);
            if (j > 0)
                D[i] = min(D[i], max(2*mx_height, building[i].X - building[j].X) + D[j - 1]);
            else
                D[i] = min(D[i], max(2*mx_height, building[i].X - building[j].X));
        }
    }
    printf("%d", D[N-1]);
}
