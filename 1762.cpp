#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define X first
#define Y second
#define pb push_back
int n;
vector<int> adj[100005];
int main(void){
  ios::sync_with_stdio(0);
  cin.tie(0);
  int m;
  cin >> n >> m;
  while(m--){
    int a,b;
    cin >> a >> b;
    adj[a].pb(b);
    adj[b].pb(a);
  }
  for(int i = 1; i <= n; i++){
    sort(adj[i].begin(),adj[i].end());
  }
  int cnt = 0;
  for(int i = 1; i <= n; i++){
    for(auto nxt : adj[i]){
      if(nxt < i) continue;
      int v1 = nxt;
      int v2 = i;
      if(adj[v1].size() > adj[v2].size()) swap(v1,v2);
      for(auto k : adj[v1])
        cnt += binary_search(adj[v2].begin(),adj[v2].end(),k);
    }    
  }
 // cout << cnt << endl;
  //assert(cnt%3==0);
  cout << cnt/3;
}
