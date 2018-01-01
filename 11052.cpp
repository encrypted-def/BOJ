#include <stdio.h>
#include <algorithm>
using namespace std;
int main(void){
    int N;
    int P[1001];
    int D[1001];
    scanf("%d", &N);
    for(int i = 1; i <= N; i++)
        scanf("%d", &P[i]);
    D[1] = P[1];
    for(int i = 2; i <= N; i++){
        D[i] = P[i];
        for(int j = 1; j <= i-1; j++)
            D[i] = max(D[i], D[j]+D[i-j]);
    }
    printf("%d", D[N]);
}
