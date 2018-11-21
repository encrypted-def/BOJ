#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define X first
#define Y second
#define pb push_back

vector<int> p(200003,-1);
tuple<int,int,int> anc[200003][20]; // ans[i][j] : 2**j-th 조상의 index, 그때까지 거치는 edge의 max, second max
int n,m;
vector<pair<int,int> > adj[200003]; // mst의 adj
tuple<int,int,int,int> edge[200003]; // cost u v idx
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
  anc[cur][0] = {p,w,0};
  for(int i =1; i < 20; i++){
    auto tmp = anc[cur][i-1];
    int ancidx = get<0>(tmp);
    int t[4];
    t[0] = get<1>(tmp);
    t[1] = get<2>(tmp);
    t[2] = get<1>(anc[ancidx][i-1]);
    t[3] = get<2>(anc[ancidx][i-1]);
    sort(t,t+4);
    anc[cur][i] = {get<0>(anc[ancidx][i-1]), t[3],t[2]};
  }
  for(auto n : adj[cur]){
    if(n.X!=p) dfs(n.X, cur, n.Y);
  }
}
pair<int,int> mx_lca(int a, int b){
  if(depth[a] > depth[b]) swap(a,b);
  set<int> ret;
  for(int i = 19; i >= 0; i--){
    if(depth[a] <= depth[get<0>(anc[b][i])]){
      ret.insert(get<1>(anc[b][i]));
      ret.insert(get<2>(anc[b][i]));
      b = get<0>(anc[b][i]);
      while(ret.size() > 2){
        ret.erase(ret.begin());
      }
    }
  }
  if(a==b){
    if(ret.size() == 1) return {*ret.begin(),0};
    else return {*next(ret.begin()),*ret.begin()};
  }
  if(a != b){
    for(int j = 19; j >= 0; j--){
      if(get<0>(anc[a][j]) != 0 and get<0>(anc[a][j]) != get<0>(anc[b][j])){
        ret.insert(get<1>(anc[a][j]));
        ret.insert(get<2>(anc[a][j]));
        ret.insert(get<1>(anc[b][j]));
        ret.insert(get<2>(anc[b][j]));
        while(ret.size() > 2) ret.erase(ret.begin());        
        a = get<0>(anc[a][j]);
        b = get<0>(anc[b][j]);
      }
    }
    ret.insert(get<1>(anc[a][0]));
    ret.insert(get<2>(anc[a][0]));
    ret.insert(get<1>(anc[b][0]));
    ret.insert(get<2>(anc[b][0]));    
    while(ret.size() > 2) ret.erase(ret.begin());  
    if(ret.size() == 1) return {*ret.begin(),0};
    else return {*next(ret.begin()),*ret.begin()};
  }
  return {-1,-1};//unreachable
}
int main(void){
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin>>n>>m;
  if(m<=n-1){
    cout << -1;
    return 0;
  }
  for(int i = 0; i < m;i++){
    int u,v,w;
    cin>>u>>v>>w;
    edge[i] = {w+1,u,v,i};
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
    if(i == m and cnt < n-1){
      cout << -1;
      return 0;
    }
  }
  dfs(1,0,0);
  ll ans = 0x78f7f7f77f;
  for(int i = 0; i < m; i++){
    int w,u,v,idx;
    tie(w,u,v,idx) = edge[i];
    auto mx = mx_lca(u,v);
    //cout << w << ' ' << mx.X << ' ' << mx.Y << '\n';
    if(mx.X != w) ans = min(ans,mst_tot-mx.X+w);
    if(mx.Y != 0) ans = min(ans,mst_tot-mx.Y+w);
  }
  if(ans == 0x78f7f7f77f) ans = -1+(n-1);
  cout << ans-(n-1);
}
