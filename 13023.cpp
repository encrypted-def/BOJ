#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define X first
#define Y second
#define pb push_back
int n;
vector<int> adj[2004];
vector<int> depth;
void dfs(int cur){
  if(depth[cur] == 5){
    cout << 1;
    exit(0);
  }
  for(auto nxt : adj[cur]){
    if(depth[nxt] != -1) continue;
    depth[nxt] = depth[cur]+1;
    dfs(nxt);
    depth[nxt] = -1;
  }
}
int main(void){
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> n;
  int m;
  cin >> m;
  while(m--){
    int a,b;
    cin>>a>>b;
    adj[a].pb(b);
    adj[b].pb(a);
  }
  for(int r = 0; r < n; r++){
    depth.resize(n);
    fill(depth.begin(),depth.end(),-1);
    depth[r] = 1;
    dfs(r);

  }
  cout << 0;
}
