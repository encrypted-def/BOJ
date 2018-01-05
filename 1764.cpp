#include <string>
#include <iostream>
#include <algorithm>
using namespace std;
int N, M;
string a[500001];
string b[500001];
string c[500001];
int main(void) {
    cin >> N >> M;
    for (int i = 0; i < N; i++)
        cin >> a[i];
    for (int i = 0; i < M; i++)
        cin >> b[i];
    sort(a, a + N);
    sort(b, b + M);
    int aidx = 0, bidx = 0, idx = 0;
    while (aidx < N && bidx < M) {
        if (a[aidx] < b[bidx])
            aidx++;
        else if (a[aidx] > b[bidx])
            bidx++;
        else {
            c[idx++] = a[aidx++];
            bidx++;
        }
    }
    cout << idx << "\n";
    for (int i = 0; i < idx; i++)
        cout << c[i] << "\n";
 
}
