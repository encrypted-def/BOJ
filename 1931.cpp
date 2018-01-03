#include <stdio.h>
#include <algorithm>
#define X first
#define Y second
using namespace std;
typedef pair<int, int> PAIR; // 끝나는 시간, 시작 시간
 
int n;
PAIR schedule[100002];
int main(void) {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d %d", &schedule[i].Y, &schedule[i].X);
    sort(schedule, schedule + n);
    int last_time = schedule[0].X; // 지금 정해진 스케쥴이 끝나는 시간이 기록
    int cnt = 1; // 지금까지 열린 회의의 수가 저장
    for (int i = 1; i < n; i++) {
        if (schedule[i].Y >= last_time) {
            cnt++;
            last_time = schedule[i].X;
        }
    }
    printf("%d", cnt);
}
