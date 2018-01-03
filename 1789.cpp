#include <stdio.h>
#include <math.h>
int main(void){
    long long int S;
    scanf("%lld", &S);
    int N = sqrt(2.0*S);
    while( 1LL * N * (N+1) / 2 <= S)
        N++;
    printf("%d", N-1);
}
