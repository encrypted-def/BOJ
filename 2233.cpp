#include<bits/stdc++.h>
using namespace std;
#define X first
#define Y second
#define pb push_back
typedef long long ll;
#include<bits/stdc++.h>
using namespace std;
#define X first
#define Y second
#define pb push_back
typedef long long ll;
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
  int cor[5005];
  int in[2003];
  int out[2003];
  int n;
  cin >> n;
  LCA l(n);
  string s;
  cin >> s;
  stack<int> S;
  int cnt = 1;
  for(int i = 0; i < 2*n; i++){
    if(s[i]=='0'){
      if(!S.empty()){
        l.pushadj(S.top(),cnt);
      }
      S.push(cnt);
      cor[i] = cnt;
      in[cnt] = i;
      cnt++;
    }
    else{
      cor[i] = S.top();
      out[S.top()] = i;
      S.pop();
    }
  }
  //cout << in[1] << in[2] << in[3] << in[4] << in[5] << '\n';
  //cout << out[1] << out[2] << out[3] << out[4] << out[5] << '\n';
  
  l.construct(1);
  int a,b;
  cin >> a >> b;
  a--; b--;
  if(cor[a]==cor[b]){
    cout << in[cor[a]]+1 << ' ' << out[cor[a]]+1;
  }
  else{
    int lca = l.lca(cor[a],cor[b]);
    //cout << "lca : " << lca << '\n';
    cout << in[lca]+1 << ' ' << out[lca]+1;
  }

}
