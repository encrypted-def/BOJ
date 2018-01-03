#include <stdio.h>
#include <algorithm>
using namespace std;
int N, M;
int tree[1000001];
int divi(int a, int b) {
    return (a / b + (a%b != 0));
}
int main(void) {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; i++)
        scanf("%d", &tree[i]);
    sort(tree, tree + N);
    int treeidx = N - 1; // 잘려나가는 tree중에 가장 작은 tree의 index
    while (true) {
        //printf("%d %d\n", M, treeidx);
        if (treeidx == 0 || divi(M, N - treeidx) <= tree[treeidx] - tree[treeidx-1]) { // treeidx-1 나무를 자르지 않고도 해결이 가능한 상황이면
            printf("%d", tree[treeidx] - divi(M, N - treeidx));
            return 0;
        }
        else {
            M -= (N - treeidx)*(tree[treeidx] - tree[treeidx - 1]);
            treeidx--;
        }
    }
}
