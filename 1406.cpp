#include <list>
#include <stdio.h>
#include <string.h>
using namespace std;
char init[100003];
int len = 0;
int main(void) {
    scanf("%s", init);
    len = strlen(init);
    list<char> L;
    for (int i = 0; i < len; i++)
        L.push_back(init[i]);
    auto cursor = L.end();
    int Q;
    scanf("%d", &Q);
    while (Q--) {
        char op[3];
        scanf("%s", op);
        if (op[0] == 'P') {
            char ins[3];
            scanf("%s", ins);
            L.insert(cursor, ins[0]);
        }
        else if (op[0] == 'L') {
            if (cursor != L.begin())
                cursor--;
        }
        else if (op[0] == 'D') {
            if (cursor != L.end())
                cursor++;
        }
        else {
            if (cursor != L.begin()) {
                cursor--;
                cursor = L.erase(cursor);
            }
        }
    }
    for (const auto& elem : L)
        printf("%c", elem);
}
