#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll INV(ll a, ll m) {
  ll m0 = m, y = 0, x = 1;
  if (m == 1)	return 0;
  while (a > 1) {
    ll q = a / m;
    ll t = m;
    m = a % m, a = t;
    t = y;
    y = x - q * y;
    x = t;
  }
  if (x < 0) x += m0;
  return x;
}




ll mobius[200005]; // 전역변수에 둘 것

void set_mobius(){
  int mx = 2e5;  
  fill(mobius+1,mobius+mx+1,1);
  for(int i = 2; i*i <= mx; i++){
    if (mobius[i] == 1) {
      for (int j = i; j <= mx; j += i) mobius[j] *= -i;
      for (int j = i * i; j <= mx; j += i * i) mobius[j] = 0;
    }
  }
  for (int i = 2; i <= mx; i++) {
    if (mobius[i] == i)
      mobius[i] = 1;
    else if (mobius[i] == -i)
      mobius[i] = -1;
    else if (mobius[i] < 0)
      mobius[i] = 1;
    else if (mobius[i] > 0)
      mobius[i] = -1;
  }
}

ll mod = 1e9+7;
ll prob1[200001]; // prob1[i] : gcd가 i의 배수일 확률
ll prob2[200001]; // prob2[i] : gcd가 i일 확률
ll a[5],b[5],inv[5];
ll factor[200001];
vector<int> div_list[200001];
int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);
  set_mobius();
  for(int i = 1; i <= 200000; i++){
    for(int j = i; j <= 200000; j += i) div_list[j].push_back(i);
  }
  for(int i = 1; i <= 200000; i++){
    for(auto j : div_list[i]){ // j는 i의 약수
      factor[i] = (mod+factor[i]+j*mobius[i/j])%mod;
    }    
  }

  int t = 50;
  cin >> t; 
  
  while(t--){
    fill(prob1,prob1+200001,1);
    fill(prob2,prob2+200001,0);    
    int k=5;
    cin >> k;
    for(int i = 0; i < k; i++) cin >> a[i] >> b[i];
    for(int i = 0; i < k; i++) inv[i] = INV(b[i]-a[i]+1,mod);
    for(int i = 1; i <= 200000; i++){
      for(int j = 0; j < k; j++){
        prob1[i] = prob1[i] * (b[j]/i - (a[j]-1)/i) % mod;
        prob1[i] = (prob1[i] * inv[j])%mod;
      }
    }
    /*for(int i = 200000; i >= 1; i--){
      prob2[i] = prob1[i];
      for(int j = 2*i; j <= 200000; j += i){
        prob2[i] = (mod + prob2[i] - prob2[j]) % mod;
      }
    }*/
    ll exp = 0;
    for(int i = 1; i <= 200000; i++)
      exp = (exp + factor[i] * prob1[i]) % mod;
    cout << mod-exp << '\n';
  }
}
