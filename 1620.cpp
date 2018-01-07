#include <string>
#include <map>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
string Num2Str[100001];
int main(void) {
    map<string, int> Str2Num;
    int N, M;
    scanf("%d %d", &N, &M);
    for (int i = 1; i <= N; i++) {
        char tmp[1000];
        scanf("%s", tmp);
        Num2Str[i] = tmp;
        Str2Num[tmp] = i;
    }
    while (M--) {
        char tmp[1000];
        scanf("%s", tmp);
        string s = tmp;
        if (s[0] >= '0' && s[0] <= '9')
            cout << Num2Str[stoi(s)] << '\n';
        else
            cout << Str2Num[s] << '\n';
    }
 
}
