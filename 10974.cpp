#include <string>
#include <iostream>
#include <stdio.h>
using namespace std;
int N;
void print_permutation(string prefix, int* isused, int left) {
    if (left == 1) {
        for (int i = 1; i <= N; i++) {
            if (!isused[i]) {
                cout << prefix + to_string(i) + " " + "\n";
                return;
            }
        }
    }
    for (int i = 1; i <= N; i++) {
        if (!isused[i]) {
            isused[i] = true;
            print_permutation(prefix + to_string(i) + " ", isused, left - 1);
            isused[i] = false;
        }
    }
}
int main(void) {
    scanf("%d", &N);
    int isused[9] = { false, };
    string prefix = "";
    print_permutation(prefix, isused, N);
}
