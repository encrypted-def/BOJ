#include <stdio.h>
int pow2(int n){
    int val = 1;
    while(n--)
        val *= 2;
    return val;
}
void next_brute(int* num, int N){
    num[N-1]++;
    for(int i = N-1; i >= 0; i--){
        if(num[i] == 2){
            num[i] = 0;
            num[i-1]++;
        }
        else
            return ;
    }
}
int main(void){
    int N, S;
    int num[20];
    int brute[20] = {0, };
    int cnt = 0;
    scanf("%d %d", &N, &S);
    for(int i = 0; i < N; i++)
        scanf("%d", &num[i]);
    brute[N-1] = 1;
    int brutelen = pow2(N)-1;
    while(brutelen--){
        int sum = 0;
        for(int i = 0; i < N; i++)
            sum += num[i] * brute[i];
        cnt += sum == S;
        next_brute(brute, N);
    }
    printf("%d", cnt);
}
