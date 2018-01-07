#include <stdio.h>
#include <algorithm>
#include <vector>
using namespace std;
int N;
int left[10004];
int right[10004];
int depth[10004];
int parent[10004];
int place[10004];
int current_place = 1;
int mn_lv[10004];
int mx_lv[10004];
void traversal(int cur) {
    if (parent[cur] != 0)
        depth[cur] = depth[parent[cur]] + 1;
    if (left[cur] != -1)
        traversal(left[cur]);
    place[cur] = current_place++;
    mn_lv[depth[cur]] = min(mn_lv[depth[cur]], place[cur]);
    mx_lv[depth[cur]] = max(mx_lv[depth[cur]], place[cur]);
    if (right[cur] != -1)
        traversal(right[cur]);
}
int main(void) {
    fill(mn_lv, mn_lv + 10004, 0xfffff);
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        int tmp;
        scanf("%d", &tmp);
        scanf("%d %d", &left[tmp], &right[tmp]);
        if(left[tmp] != -1)
            parent[left[tmp]] = tmp;
        if(right[tmp] != -1)
            parent[right[tmp]] = tmp;
    }
    int root = -1;
    for (int i = 1; i <= N; i++) {
        if (parent[i] == 0) {
            root = i;
            break;
        }
    }
    depth[root] = 1;
    traversal(root);
    int maxWidthIdx = 1;
    for (int i = 2; i < 10004; i++) {
        if (mn_lv[i] == 0xfffff)
            break;
        if (mx_lv[maxWidthIdx] - mn_lv[maxWidthIdx] < mx_lv[i] - mn_lv[i])
            maxWidthIdx = i;
    }
    printf("%d %d", maxWidthIdx, mx_lv[maxWidthIdx] - mn_lv[maxWidthIdx] + 1);    
}
