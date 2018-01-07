#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
char s1[104];
char s2[104];
char s3[104];
int len1, len2, len3;
int D[104][104][104]; // D[i][j][k] : s1[0~i-1], s2[0~j-1], s3[0~k-1]의 subsequence 중 최대 길이
 
bool eq3(char a, char b, char c) {
    return a == b && b == c;
}
int main(void) {
    int mx = 0;
    scanf("%s", s1);
    scanf("%s", s2);
    scanf("%s", s3);
    len1 = strlen(s1);
    len2 = strlen(s2);
    len3 = strlen(s3);
    for (int i = 1; i <= len1; i++) {
        for (int j = 1; j <= len2; j++) {
            for (int k = 1; k <= len3; k++) {
                if (eq3(s1[i - 1], s2[j - 1], s3[k - 1]))
                    D[i][j][k] = D[i - 1][j - 1][k - 1] + eq3(s1[i - 1], s2[j - 1], s3[k - 1]);
                else
                    D[i][j][k] = max(D[i - 1][j][k], max(D[i][j - 1][k], D[i][j][k - 1]));
                mx = max(D[i][j][k], mx);
            }
        }
    }
    printf("%d", mx);
}
