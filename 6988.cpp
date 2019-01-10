#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n;
int a[3005];
int pos[1000005];
ll d[3005][3005];
int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> n;
  fill(pos,pos+1000001,-1);
  for(int i = 0; i < n; i++){
    cin >> a[i];
    pos[a[i]]=i;
  }
  ll ans = 0;
  for(int i = 0; i < n; i++){
    for(int j = i+1; j < n; j++){
      int bb = -1;
      if(2*a[i]-a[j] >= 0) bb = pos[2*a[i]-a[j]];
      if(bb == -1) d[i][j] = a[i]+a[j];
      else{
//        cout << bb << ' ' << i << ' ' << j << '\n';
        d[i][j] = d[bb][i] + a[j];
        ans = max(ans,d[i][j]);
      }
    }
  }
  cout << ans;  
}
