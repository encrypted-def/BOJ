#include <stdio.h>
#include <algorithm>
using namespace std;
int A[100000];
int N, M;
int main(void) {
    scanf("%d", &N);
    for (int i = 0; i < N; i++)
        scanf("%d", &A[i]);
    sort(A, A + N);
    scanf("%d", &M);
    while (M--) {
        int num;
        scanf("%d", &num);
        printf("%d\n", binary_search(A, A + N, num));
    }
}
