#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pll;
typedef pair<int,int> pii;
#define X first
#define Y second
#define pb push_back
int n;
int k; // 2**k-1 = n
ll d[263000]; // 내 subtree의 용량
ll w[263000];
ll earn[263000];
ll ans[263000];
bool solve(ll t, vector<int>& arr, int idx){
  ll tot = earn[idx]*t;
  for(auto e : arr)
    tot += max(0ll, t*earn[e]-d[e]);
  return tot >= d[idx];
}
int main(){
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> n;
  while((1<<k) < n+1) k++;
  for(int i = 1; i <= n; i++) cin >> w[i];
  for(int i = n; i >= 1; i--){
    if(2*i > n){ d[i] = w[i]; earn[i] = 1;}
    else{
      d[i] = w[i]+d[2*i]+d[2*i+1];
      earn[i] = earn[2*i]*2;
    }
  }
  for(int i = 1; i <= n; i++){
    ll st = 0;
    ll en = 2e9+10;
    vector<int> arr;
    int zz = i;
    while(zz != 1){
      if(zz%2 == 0) arr.push_back(zz+1);
      else arr.push_back(zz-1);
      zz /= 2;
    }
   
    while(st<en){
      ll mid = (st+en)/2;
      if(solve(mid,arr,i)) en = mid;
      else st = mid+1;
    }
    ans[i] = st;
  }
  for(int i = 1; i <= n; i++) cout << ans[i] << ' ';
}
