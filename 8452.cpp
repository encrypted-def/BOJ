#include<bits/stdc++.h>
using namespace std;
#define X first
#define Y second
#define pb push_back
typedef long long ll;

int n,m,q;
tuple<int,int,int> edge[100004]; // {u,v,whether alive or not}
pair<char,int> query[200004];
int dist[1004];
vector<int> adj[1005];
vector<int> ans;
int main(void){
  //ios::sync_with_stdio(0);
  //cin.tie(0);
  cin >> n >> m >> q;
  fill(dist,dist+1003,0x7f7f7f);
  for(int i = 1; i <= m; i++){
    int a,b;
    cin>>a>>b;
    edge[i] = {a,b,1};
  }
  for(int i = 1; i <= q; i++){
    string a; int b;
    cin>>a>>b;
    query[i] = {a[0],b};
    if(a[0] == 'U'){
      get<2>(edge[b]) = 0;
    }
  }
  for(int i = 1; i <= m; i++){
    if(!get<2>(edge[i])) continue;
    int u = get<0>(edge[i]);
    int v = get<1>(edge[i]);
    adj[u].pb(v);
  }
  queue<int> Q;
  Q.push(1);
  dist[1] = 0;
  while(!Q.empty()){
    int cur = Q.front();
    Q.pop();
    for(auto n : adj[cur]){
      if(dist[n] > dist[cur]+1){
        dist[n] = dist[cur]+1;
        Q.push(n);
      }
    }
  }
  for(int i = q; i >= 1; i--){
    if(query[i].X == 'U'){
      int u = get<0>(edge[query[i].Y]);
      int v = get<1>(edge[query[i].Y]);
      adj[u].pb(v);
      if(dist[v] <= dist[u]+1) continue;
      dist[v] = dist[u]+1;
      queue<int> Q;
      Q.push(v);
      while(!Q.empty()){
        int cur = Q.front();
        Q.pop();
        for(auto n : adj[cur]){
          if(dist[n] > dist[cur]+1){
            dist[n] = dist[cur]+1;
            Q.push(n);
          }
        }
      }      
    }
    else{
      ans.pb(dist[query[i].Y]);
    }
  }
  reverse(ans.begin(),ans.end());  
  for(auto a : ans){
    if(a==0x7f7f7f) a=-1;
    cout << a << '\n';
  }
}
