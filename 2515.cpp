#include <stdio.h>
#include <algorithm>
#include <queue>
using namespace std;
typedef pair<int, int> PAIR;
int N, S;
int D[300005]; // D[i] : pic[0~i]를 전시할 때 최댓값. 단 i번쨰 그림은 반드시 보여짐
#define H first
#define C second
PAIR pic[300005];
int main(void) {
    scanf("%d %d", &N, &S);
    for (int i = 0; i < N; i++)
        scanf("%d %d", &pic[i].H, &pic[i].C);
    sort(pic, pic + N);
    D[0] = pic[0].C;
    int mx = D[0];
    priority_queue<int> PQ; // D[i]를 채울 때, PQ에 그림의 높이가 i번째 그림-C 이하인 k들에 대한 D[k]를 넣어두고 PQ의 top을 참고하면 된다.
    int pq_idx = 0;
    int mx_val = 0;
    for (int i = 1; i < N; i++) {
        while (pic[pq_idx].H <= pic[i].H - S) {
            mx_val = max(mx_val, D[pq_idx]);
            pq_idx++;
        }
            D[i] = mx_val + pic[i].C;
        mx = max(mx, D[i]);
    }
    printf("%d", mx);
}
