#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n;
// d1[i] : 수 i의 등장 횟수 
// d2[i] : i 배수의 등장 횟수
// d3[i] : gcd(x,y)가 i의 배수인 횟수
// d4[i] : gcd(x,y)가 i인 횟수
ll d1[3000005],d2[3000005],d3[3000005],d4[3000005];
int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> n;
  ll t;
  for(int i = 0; i < n; i++){
    cin >> t;
    d1[t]++;
  }
  
  for(int i = 3000000; i >= 1; i--){
    for(int j = i; j <= 3000000; j += i)
      d2[i] += d1[j];
  }

  for(int i = 1; i <= 3000000; i++)
    d3[i] = (d2[i]-1)*d2[i]/2;

  for(int i = 3000000; i >= 1; i--){
    d4[i] = d3[i];
    for(int j = 2*i; j <= 3000000; j += i)
      d4[i] -= d4[j];
  }
  cout << d4[1];
}
