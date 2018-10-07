#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define X first
#define Y second
#define pb push_back
vector< bool > sieve;
int calc(int p, int n){
  int cnt = 1;
  ll pp = p;
  while(pp <= n){
    pp *= p;
    cnt++;
  }
  return pp/p;
}
int main(void){
  ios::sync_with_stdio(0);
  cin.tie(0);
  int n;
  cin >> n;
  if(n==1){
    cout << 1;
    return 0;
  }
  sieve.resize(n+1,1);
  sieve[1]=0;
  unsigned int lcm = 1;
  for(int i = 2; i*i <= n; i++){
    if(!sieve[i]) continue;
    for(int j = i*i; j <= n; j+=i){
      sieve[j] = 0;
    }
  }
  int p = 2;
  for(;p*p <= n; p++){
    if(sieve[p]) lcm *= calc(p,n);
  }
  for(; p <= n; p++){
    if(sieve[p]) lcm *= p;
  }
  cout << lcm;


}
