#include <string.h>
#include <stdio.h>
#include <algorithm>
using namespace std;
char DNA[503];
int D[502][502]; // D[i][j] : DNA[i~j] 내의 가장 긴 유전자 길이
int main(void) {
    scanf("%s", DNA);
    int dna_len = strlen(DNA);
    for (int len = 2; len <= dna_len; len++) {
        for (int st = 0; st < dna_len; st++) { // D[st][st+len-1]을 계산할 것임
            if (st + len > dna_len)
                break;
            int en = st + len - 1;
            for (int sep = st; sep <= en-1; sep++) // D[st][sep]+D[sep+1][en]으로 계산할 계획
                D[st][en] = max(D[st][en], D[st][sep] + D[sep + 1][en]);
            // 2개로 분리되지 않고 하나 안에 다 포함되는 경우
            if ((DNA[st] == 'a' && DNA[en] == 't') || (DNA[st] == 'g' && DNA[en] == 'c'))
                D[st][en] = max(D[st][en], D[st + 1][en - 1] + 2);
        }
    }
    printf("%d", D[0][dna_len - 1]);
}
