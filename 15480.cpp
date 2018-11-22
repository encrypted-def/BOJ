#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define X first
#define Y second
#define pb push_back

class LCA{ // 1-indexed 
public:
  vector< vector<int> > adj,anc; // anc[i][j] : 2**j-th ancestor of i
  vector<int> depth;
  int n, mxdepth;
  LCA(int n):n(n),adj(n+1),depth(n+1),anc(n+1){
    mxdepth = 33 - __builtin_clz(n);
    for(int i = 0; i <= n; i++) anc[i].resize(mxdepth);
  }
  void construct(int cur, int p){
    depth[cur] = depth[p]+1;
    anc[cur][0] = p;
    for(int i = 1; i < mxdepth; i++) anc[cur][i] = anc[anc[cur][i-1]][i-1];
    for(auto n : adj[cur]){
      if(n != p) construct(n,cur);
    }
  }
  void construct(int root){ // set anc table
    construct(root,0);
  }
  int lca(int a, int b){ // returns lca of a,b
    if(depth[a] > depth[b]) swap(a,b);
    for(int i = mxdepth - 1; i >= 0; i--){
      if(depth[a] <= depth[anc[b][i]]) b = anc[b][i];
        
    }
    int ret = a;
    if(a != b){
      for(int j = mxdepth-1; j >= 0; j--){
        if(anc[a][j] != 0 and anc[a][j] != anc[b][j]){
          a = anc[a][j];
          b = anc[b][j];
        }
      }
      ret = anc[a][0];
    }
    return ret;
  }
  void pushadj(int a, int b){
    adj[a].pb(b);
    adj[b].pb(a);
  }
};

int main(void){
  ios::sync_with_stdio(0);
  cin.tie(0);
  int n;
  cin>>n;
  LCA L(n);
  for(int i = 0; i < n-1; i++){
    int u,v;
    cin>>u>>v;
    L.pushadj(u,v);
  }
  L.construct(1);
  int m;
  cin >> m;
  while(m--){
    int r,u,v;
    cin>>r>>u>>v;
    int v1 = L.lca(u,v);
    int v2 = L.lca(r,u);
    int v3 = L.lca(r,v);
    if(L.depth[v1] < L.depth[v2]) v1 = v2;
    if(L.depth[v1] < L.depth[v3]) v1 = v3;
    cout << v1 << '\n';
  }
}
