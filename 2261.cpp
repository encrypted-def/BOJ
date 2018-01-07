#include <stdio.h>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long LL;
typedef pair<LL, LL> PAIR;
#define X first
#define Y second
#define MAX 1000000000000ll;
PAIR point[500004];
int n;
 
LL square(LL a) {
    LL ans = a*a;
    return ans;
}
LL dist(PAIR a, PAIR b) {
    LL ans = square(a.X - b.X) + square(a.Y - b.Y);
    return ans;
}
bool op(PAIR a, PAIR b) {
    if (a.Y != b.Y)
        return a.Y < b.Y;
    else
        return a.X < b.X;
}
LL solve(PAIR* point, int st, int en) { // point[st:en]에서의 가까운 두 점의 거리의 제곱을 반환하는 함수
    if (en - st == 1)
        return MAX;
    int mid = (st + en) / 2;
    LL d = min(solve(point, st, mid), solve(point, mid, en));
    vector<PAIR> V; // point[st:en]에서 기준선으로부터 거리가 sqrt(d) 이하로 떨어진 점들을 담을 vector
    LL sep = point[mid].X; // x = point[mid].X가 기준선
    for (int i = st; i < en; i++) {
        if (square(point[i].X - sep) <= d)
            V.push_back(point[i]);
    }
    sort(V.begin(), V.end(), op); // y좌표 기준으로 정렬
    for (int i = 0; i < V.size(); i++) {
        for (int j = i + 1; j < V.size() && j < i + 7; j++) { // 인접한 6개의 점에 대해
            d = min(d, dist(V[i], V[j])); // d를 갱신
        }
    }
    return d;
}
 
int main(void) {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%lld %lld", &point[i].X, &point[i].Y);
    sort(point, point + n);
    printf("%lld\n", solve(point, 0, n));
 
}
