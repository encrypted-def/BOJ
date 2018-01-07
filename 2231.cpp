#include <stdio.h>
int dec_sum[1000001];
int main(void) {
    for (int i = 1; i <= 1000000; i++) {
        int tmp = i;
        int sum = tmp;
        while (tmp > 0) {
            sum += tmp % 10;
            tmp /= 10;
        }
        dec_sum[i] = sum;
    }
    int N;
    scanf("%d", &N);
    for (int i = 1; i <= 1000000; i++) {
        if (dec_sum[i] == N) {
            printf("%d", i);
            return 0;
        }
    }
    printf("0");
    return 0;
}
