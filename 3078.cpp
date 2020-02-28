#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int n,k;
vector<int> occur[25];
int main(){
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> n >> k;
  string s;
  ll tot = 0;
  for(int i = 0; i < n; i++){
    cin >> s;
    occur[s.size()].push_back(i);
  }
  for(int i = 2; i <= 20; i++){
    for(int j = 0; j < occur[i].size(); j++)
      tot += occur[i].begin() + j -lower_bound(occur[i].begin(),occur[i].end(),occur[i][j]-k);
  }
  cout << tot;
}
