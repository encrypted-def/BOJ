#include <stdio.h>
#include <algorithm>
using namespace std;
typedef long long LL;
#define X first
#define Y second
LL x[50001];
LL v[50001];
int N;
double T;
double left_reach(LL x, LL v){
    return x - v*T;
}
double right_reach(LL x, LL v) {
    return x + v*T;
}
int main(void) {
    scanf("%d %lf", &N, &T);
    for (int i = 0; i < N; i++)
        scanf("%lld", &x[i]);
    for (int i = 0; i < N; i++)
        scanf("%lld", &v[i]);
    pair<double, double> bound; // 학생들이 T초간 도달할 수 있는 범위. 이 범위에 포함할 수 없는 학생이 주어지면 만날 수 없는 것임
    bound.X = left_reach(x[0], v[0]);
    bound.Y = right_reach(x[0], v[0]);
    for (int i = 1; i < N; i++) {
        double left = left_reach(x[i], v[i]);
        double right = right_reach(x[i], v[i]);
        if (bound.Y < left || bound.X > right) { // i번째 학생이 0~i-1번째 학생 누군가와는 전혀 만날 수 없는 경우.(bound와 교집합이 없음)
            printf("0");
            return 0;
        }
        if (left <= bound.X && right >= bound.Y) // i번째 학생이 이동할 수 있는 범위가 bound를 포함할 경우
            continue; // bound는 그대로
        else if (bound.X <= left && bound.Y >= right) { // bound가 i번째 학생이 이동할 수 있는 범위를 포함할 경우
            bound.X = left;
            bound.Y = right; // bound를 축소
        }
        else if (left <= bound.X) // left bound.X right bound.Y 순서로 놓여있는 상황임
            bound.Y = right;
 
        else // bound.X left bound.Y right 순서로 놓여있는 상황임
            bound.X = left;
    }
    printf("1"); // 여기까지 도달한건 만날 수 있는 지점이 있는것임
}
