#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pll;
typedef pair<int,int> pii;
#define X first
#define Y second
#define pb push_back
int n;
vector<pii> node[9000001];
int idx = 1;
ll mod = 1e9+7;
ll fact[28];
int main(){
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> n;
  fact[0] = 1;
  for(int i = 1; i <= 27; i++) fact[i] = fact[i-1]*i%mod;
  for(int i = 0; i < n; i++){
    string s;
    cin >> s;
    s += '+';
    int cur = 1;
    for(auto c : s){
      bool find = 0;
      for(auto e : node[cur]){
        if(e.X == c-'A'){
          find = 1;
          cur = e.Y;
        }
      }
      if(!find){
        idx++;
        node[cur].pb({c-'A',idx});
        cur = idx;
      }
    }
  }
  ll ans = 1;
  for(int i = 1; i <= idx; i++){
    //cout << i << ' ' << node[i].size() << '\n';
    ans = ans * fact[node[i].size()] % mod;
  }
  cout << ans;
}
