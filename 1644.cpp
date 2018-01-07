#include <stdio.h>
#include <vector>
using namespace std;
vector<int> p_list;
bool isPrime[4000001];
void sieve() {
    for (int i = 2; i <= 4000000; i++)
        isPrime[i] = true;
    for (int curPrime = 2; curPrime <= 4000000; curPrime++) {
        if (!isPrime[curPrime])
            continue;
        p_list.push_back(curPrime);
        for (int composite = 2 * curPrime; composite <= 4000000; composite += curPrime)
            isPrime[composite] = false;
    }
}
int main(void) {
    sieve();
    int N;
    scanf("%d", &N);
    int cnt = 0;
    for (int i = 0; i < p_list.size(); i++) {
        if (N < p_list[i])
            break;
        int tmp = i;
        int sum = 0;
        while (sum < N && tmp < p_list.size())
            sum += p_list[tmp++];
        if (sum == N)
            cnt++;
    }
    printf("%d", cnt);
}
