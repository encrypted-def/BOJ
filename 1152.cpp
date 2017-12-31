#include <stdio.h>
#include <string.h>
int main(void) {
    int cnt = 0;
    bool isword = false;
    while(true){
        char c;
        if (scanf("%c", &c) == EOF)
            break;
        if (c == '\n')
            break;
        if (c == ' ')
            isword = false;
        else {
            if (!isword) cnt++;
            isword = true;
        }
    }
    printf("%d", cnt);
}
