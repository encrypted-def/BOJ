#include <bits/stdc++.h>
using namespace std;

int cnt[400005];

int main(){
  ios::sync_with_stdio(0);
  cin.tie(0);
  int n,m,k;
  cin >> n >> m >> k;
  for(int i = 1; i <= 4*n; i++) cnt[i%k]++;
  for(int i = 0; i < 2*m; i++){
    int t;
    cin >> t;
    cnt[t%k]--;
  }
  int a,b;
  cin >> a >> b;
  int diff = abs(a%k - b%k);
  cnt[a%k]--; cnt[b%k]--;
  int ans = 0;
  int val = 0;
  for(int i = diff+1; i < k; i++){
    val += cnt[i-diff-1];
    ans += min(val, cnt[i]);
    val -= min(val, cnt[i]);
  }
  cout << min(ans, m-1);
}
