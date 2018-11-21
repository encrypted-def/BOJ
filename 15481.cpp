#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define X first
#define Y second
#define pb push_back

vector<int> p(200003,-1);
pair<int,int> anc[200003][20]; // ans[i][j] : 2**j-th 조상의 index, 그때까지 거치는 edge의 최댓값
int n,m;
vector<pair<int,int> > adj[200003]; // mst의 adj
tuple<int,int,int,int> edge[200003]; // cost u v idx
ll ans[200003];
int depth[200003];

int find(int x){
  if(p[x] < 0) return x;
  return p[x] = find(p[x]);
}
int uni(int a, int b){
  a = find(a);
  b = find(b);
  if(a==b) return 0;
  if(-p[a] < -p[b]) swap(a,b);
  p[a] += p[b];
  p[b] = a;
  return 1;
}

void dfs(int cur, int p, int w){
  depth[cur] = depth[p]+1;
  anc[cur][0] = {p,w};
  for(int i =1; i < 20; i++){
    auto tmp = anc[cur][i-1];
    anc[cur][i] = {anc[tmp.X][i-1].X, max(tmp.Y, anc[tmp.X][i-1].Y)};
  }
  for(auto n : adj[cur]){
    if(n.X!=p) dfs(n.X, cur, n.Y);
  }
}
int mx_lca(int a, int b){
  if(depth[a] > depth[b]) swap(a,b);
  int ret = 0;
  for(int i = 19; i >= 0; i--){
    if(depth[a] <= depth[anc[b][i].X]){
      ret = max(ret,anc[b][i].Y);
      b = anc[b][i].X;
    }
  }
  if(a==b) return ret;
  if(a != b){
    for(int j = 19; j >= 0; j--){
      if(anc[a][j].X != 0 and anc[a][j].X != anc[b][j].X){
        ret = max(ret, anc[a][j].Y);
        ret = max(ret,anc[b][j].Y);
        a = anc[a][j].X;
        b = anc[b][j].X;
      }
    }
    ret = max(ret, anc[a][0].Y);
    ret = max(ret, anc[b][0].Y);
    return ret;
  }
  return -1;//unreachable
}
int main(void){
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin>>n>>m;
  for(int i = 0; i < m;i++){
    int u,v,w;
    cin>>u>>v>>w;
    edge[i] = {w,u,v,i};
  }
  sort(edge,edge+m);
  ll mst_tot = 0;
  int cnt = 0;
  int i=0;
  while(cnt < n-1){
    int w,u,v,idx;
    tie(w,u,v,idx) = edge[i++];
    if(!uni(u,v)) continue;
    mst_tot += w;
    cnt++;
    adj[u].pb({v,w});
    adj[v].pb({u,w});
  }
  dfs(1,0,0);
  for(int i = 0; i < m; i++){
    int w,u,v,idx;
    tie(w,u,v,idx) = edge[i];
    int mx = mx_lca(u,v);
    ans[idx] = mst_tot - mx + w;
  } 
  for(int i = 0; i < m; i++){
    cout << ans[i] << '\n';
  }


}
