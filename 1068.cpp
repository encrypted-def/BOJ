#include <stdio.h>
#include <vector>
#include <stack>
using namespace std;
int parent[52];
int N;
vector<int> sibling[52];
int main(void) {
    int root = -1;
    int del_node;
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &parent[i]);
        if (parent[i] == -1)
            root = i;
        else
            sibling[parent[i]].push_back(i);
    }
    scanf("%d", &del_node);
    if (del_node == root) {
        printf("0");
        return 0;
    }
    int cnt = 0;
    stack<int> S;
    S.push(root);
    while (!S.empty()) {
        int cur = S.top();
        S.pop();
        if (sibling[cur].size() == 0 || (sibling[cur].size() == 1 && sibling[cur][0] == del_node))
            cnt++;
        for (auto const &next : sibling[cur]) {
            if (next != del_node)
                S.push(next);
                
        }
    }
    printf("%d", cnt);
}
