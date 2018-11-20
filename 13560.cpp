#include<bits/stdc++.h>
using namespace std;
#define X first
#define Y second
#define pb push_back
typedef long long ll;

int main(void){
  ios::sync_with_stdio(0);
  cin.tie(0);
  int n;
  cin>> n;
  vector<int> a(n);
  for(int i = 0; i < n;i++) cin >> a[i];
  sort(a.begin(),a.end());
  int tot = 0;
  for(int i = 0; i < n ; i++){
    tot += a[i];
    if(tot < i*(i+1)/2){
      cout << -1;
      return 0;
    }
  }
  if(tot != n*(n-1)/2){
    cout << -1;
    return 0;
  }
  cout << 1;
  
}
