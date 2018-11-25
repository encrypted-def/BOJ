#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define X first
#define Y second
#define pb push_back

int n;
int a[100005],binv[100005],c[100005];
vector<int> d;
int main(void){
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> n;
  for(int i = 0; i < n; i++) cin >> a[i];
  for(int i = 0; i < n; i++){
    int t;
    cin >> t;
    binv[t] = i;
  }
  for(int i = 0; i < n; i++){
    c[i] = binv[a[i]];
  }
  d.pb(c[0]);
  for(int i = 1; i < n; i++){
    if(d.back() < c[i]){
      d.pb(c[i]);
    }
    else{
      *lower_bound(d.begin(),d.end(), c[i]) = c[i];
    }
  }
  cout << d.size();
}
