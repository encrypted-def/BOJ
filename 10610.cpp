#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <functional>
using namespace std;
int main(void){
    char num[100005];
    scanf("%s", num);
    int len = strlen(num);
    sort(num, num + len, greater<char>());
    int cnt = 0;
    for (int i = 0; i < len; i++)
        cnt += (num[i] - '0');
    if (cnt % 3 == 0 && num[len - 1] == '0')
        printf("%s", num);
    else
        printf("-1");
}
