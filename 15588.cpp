#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define X first
#define Y second
#define pb push_back
ll POW(ll a, ll b, ll m){
  ll ret = 1;
  for (; b; b >>= 1, a = (a * a) % m)
    if (b & 1) ret = (ret * a) % m;
  return ret;
}
int mod = 1e9+7;
ll d[1000005];
int n,m,k;
int main(void){
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin>>n>>m>>k;
  if(k==1){
    cout << POW(m,n,mod);
    return 0;
  }
  ll tot = d[1] = m;
  for(int i = 2; i <= k-1; i++){
    d[i] = d[i-1]*m%mod;
    tot = (tot+d[i])%mod;
  }
  for(int i = k; i <= n; i++){
    d[i] = tot*(m-1)%mod;
    tot = (mod+tot-d[i-k+1]+d[i])%mod;
  }
  //for(int i = 1; i <= n; i++) cout << d[i] << ' ';
  cout << (mod+POW(m,n,mod)-d[n])%mod;
}
