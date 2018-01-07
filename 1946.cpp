#include <stdio.h>
int grade[100004]; // grade[i] : 서류심사 성적이 i등인 사람의 면접 성적 등수
int N;
int main(void) {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &N);
        for (int i = 0; i < N; i++) {
            int a, b;
            scanf("%d %d", &a, &b);
            grade[a] = b;
        }
        int cnt = 0;
        int tmpMinGrade = 100005;
        for (int i = 1; i <= N; i++) {
            if (tmpMinGrade > grade[i]) { // 나보다 서류심사 등수가 좋은 사람들의 면접 등수 최솟값보다 내 면접 성적이 더 좋을 경우
                cnt++;
                tmpMinGrade = grade[i];
            }
        }
        printf("%d\n", cnt);
    }
}
