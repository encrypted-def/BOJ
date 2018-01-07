#include <string.h>
#include <stdio.h>
#include <stack>
#include <algorithm>
using namespace std;
typedef pair<char, int> PAIR;
char str[1000004];
char explode[38];
char result[1000004];
int main(void) {
    scanf("%s", str);
    scanf("%s", explode);
    int str_len = strlen(str);
    int explode_len = strlen(explode);
    int st_idx = 0;
    stack<PAIR> S;
    int match_len = 0;
    for (int i = 0; i < str_len; i++) {
        if (str[i] == explode[match_len])
            match_len++;
        else if (str[i] == explode[0])
            match_len = 1;
        else
            match_len = 0;
        S.push({ str[i], match_len });
        if (match_len == explode_len) {
            for (int i = 0; i < explode_len; i++)
                S.pop();
            if (!S.empty())
                match_len = S.top().second;
            else
                match_len = 0;
        }
    }
    int stack_sz = S.size();
    if (stack_sz == 0) {
        printf("FRULA");
        return 0;
    }
    result[stack_sz] = 0;
    for (int i = stack_sz - 1; i >= 0; i--) {
        result[i] = S.top().first;
        S.pop();
    }
    printf("%s", result);
}
