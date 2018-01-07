#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
char s1[4005];
char s2[4005];
int D[4005][4005]; // D[i][j] : s1[0~i-1], s2[0~j-1]에서 s1[i-1], s2[j-1]을 포함하는 가장 긴 공통 부분 문자열의 길이
int len1, len2;
int main(void){
    scanf("%s", s1);
    scanf("%s", s2);
    len1 = strlen(s1);
    len2 = strlen(s2);
    int mx = 0;
    for (int i = 1; i <= len1; i++) {
        for (int j = 1; j <= len2; j++) {
            D[i][j] = (s1[i - 1] == s2[j - 1]) * (1 + D[i - 1][j - 1]);
            mx = max(mx, D[i][j]);
        }
    }
    printf("%d", mx);
}
