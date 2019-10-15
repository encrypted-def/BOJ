#include <bits/stdc++.h>

using namespace std;


#define X first
#define Y second
typedef long long ll;
#define pb push_back
typedef pair<int,int> pii;
typedef tuple<int,int,int> ti3;



vector<ll> val(1200001); // 시작점의 값
vector<ll> lazy1(1200001,1);
vector<ll> lazy2(1200001);

const ll mod = 1e9+7;

void upd_lazy(int node, int node_st, int node_en){
  val[node] = (lazy1[node]*val[node]+lazy2[node]*(node_en-node_st+1))%mod;
  if(node_st != node_en){
    for(int child : {2*node,2*node+1}){
      lazy1[child] = (lazy1[child]*lazy1[node])%mod;
      lazy2[child] = (lazy2[child]*lazy1[node] + lazy2[node])%mod;
    }
  }
  lazy1[node] = 1;
  lazy2[node] = 0;
}

// add x
void upd1(int x, int i, int j, int node, int node_st, int node_en){
  if(j < node_st or i > node_en) return;
  if(lazy1[node] != 1 or lazy2[node] != 0)
    upd_lazy(node, node_st, node_en);
  if(i <= node_st and node_en <= j){
    lazy2[node] = x;
    upd_lazy(node, node_st, node_en);
    return;
  }
  int mid = (node_st+node_en)/2;
  upd1(x, i, j, 2*node, node_st, mid);
  upd1(x, i, j, 2*node+1, mid+1, node_en);
  val[node] = (val[2*node]+val[2*node+1])%mod;
}

// mul 2
void upd2(int i, int j, int node, int node_st, int node_en){
  if(j < node_st or i > node_en) return;
  if(lazy1[node] != 1 or lazy2[node] != 0)
    upd_lazy(node, node_st, node_en);
  if(i <= node_st and node_en <= j){
    lazy1[node] = 2;
    upd_lazy(node, node_st, node_en);
    return;
  }
  int mid = (node_st+node_en)/2;
  upd2(i, j, 2*node, node_st, mid);
  upd2(i, j, 2*node+1, mid+1, node_en);
  val[node] = (val[2*node]+val[2*node+1])%mod;
}

// sum of i to j
ll query(int i, int j, int node, int node_st, int node_en){
  //cout << node << ' ' << node_st << ' ' << node_en << '\n';
  if(j < node_st or i > node_en) return 0;
  if(lazy1[node] != 1 or lazy2[node] != 0)
    upd_lazy(node, node_st, node_en);
  if(i <= node_st and node_en <= j) return val[node];
  int mid = (node_st+node_en)/2;
  return (query(i, j, 2*node, node_st, mid) + query(i, j, 2*node+1, mid+1, node_en))%mod;
}

// etc
int num[300005]; // 각 그룹의 사람 수 
ll pow2[300005];
vector<pair<ll,int> > cumulate[300005]; 
vector<int> mul2_group;
int cur_pow2[300005];
int last_finite_gp = 1;
int occupy0[300005];

int main(void){
  ios::sync_with_stdio(0);
  cin.tie(0);
  fill(occupy0,occupy0+300001,1);
  pow2[0] = 1;
  for(int i = 1; i <= 300003; i++) pow2[i] = (pow2[i-1]*2)%mod;
  int gidx = 1;
  num[gidx] = 0;
  gidx++;
  int Q;
  cin >> Q;
  for(int q = 1; q <= Q; q++){
    /*cout << "------cumulate[0]------\n";
    for(auto x : cumulate[0]){
      cout << x.X << ' ' << x.Y << '\n';
    }
    cout << "-----------------------\n";
    cout << "------cumulate[1]------\n";
    for(auto x : cumulate[1]){
      cout << x.X << ' ' << x.Y << '\n';
    }
    cout << "-----------------------\n";*/
    /*for(int i = 1; i <= 12; i++){
      cout << query(i, i, 1, 1, 300000) << ' ';
    }
    cout << '\n';
    for(int i = 1; i <= 12; i++){
      cout << cur_pow2[i] << ' ';
    }
    cout << '\n';*/
    int z;
    cin >> z;
    if(z == 1){
      int k;
      cin >> k;
      num[gidx] = k;
      if(k == 0){
        mul2_group.pb(gidx);
        int gg = mul2_group.size();
        occupy0[gg] = occupy0[gg-1];
        upd2(1, gidx-1, 1, 1, 300000); // 시작점 *2
        upd1(1, gidx, gidx, 1, 1, 300000); // 시작점 +1
      }
      else{
        upd1(k, 1, gidx-1, 1, 1, 300000); // 시작점+k
        ll cur = 0;
        int gg = mul2_group.size();
        occupy0[gg] = gidx;
        if(!cumulate[gg].empty()) cur = cumulate[gg].back().X;
        cumulate[gg].pb({cur+k, gidx});
      }
      if(num[gidx]==0) cur_pow2[gidx] = cur_pow2[gidx-1]+1;
      else cur_pow2[gidx] = cur_pow2[gidx-1];
      gidx++;
    }
    else if(z==2){
      int g, x;
      cin >> g >> x;
      g++;
      ll start = query(g, g, 1, 1, 300000);
      x--;
      //cout << "start : " << start << '\n';
      int diff = cur_pow2[gidx-1]-cur_pow2[g-1];
      //cout << "diff : " << diff << '\n';
      cout << (start + x * pow2[diff])%mod << '\n';
    }
    else{
      int x;
      cin >> x;
      int gg = mul2_group.size();
      int ans = 0;
      while(true){
        //cout << "now x : " << x << '\n';
        //cout << "gg : " << gg << '\n';
        if(x==0){
          ans = occupy0[gg]-1;
          break;          
        }
        if(cumulate[gg].empty()){
          if(gg == 0) break;
          if(x%2 == 1){
            ans = mul2_group[gg-1]-1;
            break;
          }
          else{
            x = x/2;
            gg--;
          }   
        }
        else{
          if(cumulate[gg].back().X <= x){
            x -= cumulate[gg].back().X;
            if(gg == 0) break;
            if(x%2 == 1){
              ans = mul2_group[gg-1]-1;
              break;
            }
            else{
              x = x/2;
              gg--;
            }
          }
          else{ // catch the ans!
            ll val = cumulate[gg].back().X-x;
            auto it  = lower_bound(cumulate[gg].begin(),cumulate[gg].end(),make_pair(val,-1));
            ans = (it->Y)-1;
            break;
          }
        }
      }
      cout << ans << '\n';
    }
  }
}
