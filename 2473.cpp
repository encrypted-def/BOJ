#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
vector<ll> pos, neg;
vector<tuple<ll,int,int>> pos2, neg2;
int n;

ll v1,v2,v3;
int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);
  v1 = v2 = v3 = 0x7f7f7f7f7f7f;
  cin >> n;
  for(int i = 0; i < n; i++){
    ll a;
    cin >> a;
    if(a <= 0) neg.push_back(-a);
    else pos.push_back(a);
  }
  sort(pos.begin(), pos.end());
  sort(neg.begin(), neg.end());
  if(neg.empty()){
    cout << pos[0] << ' ' << pos[1] << ' ' << pos[2];
    return 0;
  }
  if(pos.empty()){
    cout << -neg[2] << ' ' << -neg[1] << ' ' << -neg[0];
    return 0;
  }
  for(int i = 0; i < pos.size(); i++){
    for(int j = i+1; j < pos.size(); j++){
      pos2.push_back({pos[i]+pos[j],i,j});
    }
  }

  for(int i = 0; i < neg.size(); i++){
    for(int j = i+1; j < neg.size(); j++){
      neg2.push_back({neg[i]+neg[j],i,j});
    }
  }

  sort(pos2.begin(), pos2.end());
  sort(neg2.begin(), neg2.end());
  
  for(ll x : pos){
    auto it = lower_bound(neg2.begin(), neg2.end(), make_tuple(x, -1, -1));
    if(it != neg2.begin()){
      ll val,i,j;
      tie(val,i,j) = *prev(it);     
      if(abs(-x + val) < abs(v1 + v2 + v3)){
        v1 = -neg[j]; v2 = -neg[i]; v3 = x; 
      }    
    }
    if(it != neg2.end()){
      ll val,i,j;
      tie(val,i,j) = *it;
      if(abs(-x + val) < abs(v1 + v2 + v3)){
        v1 = -neg[j]; v2 = -neg[i]; v3 = x; 
      }       
    }
  }  

  for(ll x : neg){
    auto it = lower_bound(pos2.begin(), pos2.end(), make_tuple(x, -1, -1));
    if(it != pos2.begin()){
      ll val,i,j;
      tie(val,i,j) = *prev(it);
      if(abs(-x + val) < abs(v1 + v2 + v3)){
        v1 = -x; v2 = pos[i]; v3 = pos[j];    
      }  
    }
    if(it != pos2.end()){
      ll val,i,j;
      tie(val,i,j) = *it;
      if(abs(-x + val) < abs(v1 + v2 + v3)){
        v1 = -x; v2 = pos[i]; v3 = pos[j];  
      }     
    }
  }
  cout << v1 << ' ' << v2 << ' ' << v3;
}
