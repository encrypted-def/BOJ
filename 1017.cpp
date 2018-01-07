#include <stdio.h>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
// 0 : 시작점, 1~N : 리스트의 수(왼쪽), N+1~2N : 리스트의 수(오른쪽), 2N+1 : 도착점
int residual[500][500];
int N;
int arr[53];
int isPrime[2010];
void sieve() {
    fill(isPrime, isPrime + 2004, true);
    isPrime[1] = false;
    for (int p = 2; p < 2001; p++) {
        if (!isPrime[p])
            continue;
        for (int mul = 2 * p; mul < 2001; mul += p)
            isPrime[mul] = false;
    }
}
int flow(int S, int E) {
    int parent[500];
    int cnt = 0;
    while (true) {
        fill(parent, parent + E + 1, -1);
        parent[0] = -2;
        queue<int> Q;
        Q.push(0);
        while (!Q.empty()) {
            int cur = Q.front();
            Q.pop();
            for (int i = 0; i <= E; i++) {
                if (residual[cur][i] > 0 && parent[i] == -1) {
                    Q.push(i);
                    parent[i] = cur;
                }
            }
        }
        if (parent[E] == -1) // end에 도달할 수 없을 경우
            break;
        // 경로를 거슬러 올라감
        int p = E;
        while (p != 0) {
            int pp = parent[p];
            residual[pp][p] -= 1;
            residual[p][pp] += 1;
            p = pp;
        }
        cnt++;
    }
    return cnt;
}
void init(int idx) {
    for (int i = 1; i <= N; i++) {
        residual[0][i] = 1;
        residual[N + i][2 * N + 1] = 1;
    }
    residual[0][1] = 0;
    residual[0][idx] = 0;
    residual[N + 1][2 * N + 1] = 0;
    residual[N + idx][2 * N + 1] = 0;
    for (int i = 1; i <= N; i++) {
        for (int j = i + 1; j <= N; j++) {
            residual[i][N + j] = isPrime[arr[i] + arr[j]];
            residual[j][N + i] = isPrime[arr[i] + arr[j]];
        }
    }
}
int main(void) {
    sieve();
    scanf("%d", &N);
    for (int i = 1; i <= N; i++)
        scanf("%d", &arr[i]);
    vector<int> ans;
    for (int i = 2; i <= N; i++) {
        if (!isPrime[arr[1] + arr[i]])
            continue;
 
        init(i);
        if (flow(0, 2 * N + 1) == N - 2) // flow를 다 흘려보낼 수 있으면
            ans.push_back(arr[i]);
    }
    sort(ans.begin(), ans.end());
    if (ans.empty())
        printf("-1");
    else
        for (auto val : ans)
            printf("%d ", val);
}
