#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// d1[i] : gcd(x,y)가 i의 배수인 횟수
// d2[i] : gcd(x,y)가 i인 횟수
ll d1[10000005],d2[10000005];
ll a,b,c,d;
int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> a >> b >> c >> d; a--; c--;
  for(int i = 1; i <= 10000000; i++){
    d1[i] = (b/i-a/i) * (d/i-c/i);
  }
  
  for(int i = 10000000; i >= 1; i--){
    d2[i] = d1[i];
    for(int j = 2*i; j <= 10000000; j += i)
      d2[i] -= d2[j];
  }
  cout << d2[1];
}
