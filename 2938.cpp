#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define X first
#define Y second
#define pb push_back

int n;
vector<int> a[3];
int main(void){
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> n;
  if(n==1){
    int t;
    cin >> t;
    cout << t;
    return 0;
  }
  for(int i = 0; i < n; i++){
    int t;
    cin>>t;
    a[t%3].pb(t);
  }
  if(a[0].size() == 0){
    if(a[1].size() != 0 and a[2].size() != 0){
      cout << -1;
      return 0;
    }
    for(auto e : a[1]) cout << e << ' ';
    for(auto e : a[2]) cout << e << ' ';
    return 0;
  }
  int sz0 = a[0].size();
  if(sz0 == 1){
    for(auto e : a[1]) cout << e << ' ';
    cout << a[0][0] << ' ';
    for(auto e : a[2]) cout << e << ' ';    
    return 0;
  }
  if(a[1].size() + a[2].size() +1 < a[0].size()){
    cout << -1;
    return 0;
  }
  vector<int> seq;
  for(int i = 0 ; i < sz0; i++){
    seq.pb(a[0][i]);
    if(i != sz0-1){
      if(!a[1].empty()){
        seq.pb(a[1].back());
        a[1].pop_back();
      }
      else{
        seq.pb(a[2].back());
        a[2].pop_back();
      }
    }
  }  
  for(auto e : a[1]) cout << e << ' ';
  for(auto e : seq) cout << e << ' ';   
  for(auto e : a[2]) cout << e << ' ';     
}
