#include <bits/stdc++.h>
#define X first
#define Y second
#define pb push_back
typedef long long ll;

using namespace std;
const ll INF = 0x7f7f7f7f7f7f7f7f;

class seg{
public:
  vector<ll> lmax, rmax, allmax, tot, d;
  int n;
  seg(int n):lmax(4*n),rmax(4*n),allmax(4*n),tot(4*n),d(n+1),n(n){}
  void add(int i, int x, int node, int nl, int nr){
    if(i < nl or i > nr) return;
    tot[node] += x;
    if(nl == nr){
      lmax[node] = rmax[node] = d[i];
      allmax[node] = max(0ll,d[i]);
      return;
    }
    int mid = (nl+nr)/2;
    add(i, x, 2*node, nl, mid);
    add(i, x, 2*node+1, mid+1, nr);
    lmax[node] = max({lmax[2*node], tot[2*node]+lmax[2*node+1]});
    rmax[node] = max({rmax[2*node+1], tot[2*node+1]+rmax[2*node]});
    allmax[node] = max({0ll, allmax[2*node], allmax[2*node+1], lmax[node], rmax[node], rmax[2*node]+lmax[2*node+1]});
  }
  // x만큼 변화
  void add(int i, int x){
    d[i] += x;
    add(i, x, 1, 1, n);
  }
  ll get(){
    return allmax[1];
  }
};

int n;
tuple<int,int,int> gold[3005];
vector<int> coorx,coory;
vector<pair<int,int> > gg[3005];
int main(){
  ios::sync_with_stdio(0);
  cin.tie(0);

  cin >> n;
  for(int i = 0; i < n; i++){
    int x,y,w;
    cin >> x >> y >> w;
    gold[i] = {x,y,w};
    coorx.pb(x);
    coory.pb(y);
  }
  coory.pb(-1e9-10);  
  sort(coory.begin(),coory.end());
  coorx.pb(-1e9-10);  
  sort(coorx.begin(),coorx.end());
  coorx.erase(unique(coorx.begin(),coorx.end()),coorx.end());
  coory.erase(unique(coory.begin(),coory.end()),coory.end());  

  for(int i = 0; i < n; i++){
    int x,y,w;
    tie(x,y,w) = gold[i];
    x = lower_bound(coorx.begin(),coorx.end(),x)-coorx.begin();  
    y = lower_bound(coory.begin(),coory.end(),y)-coory.begin();
    gg[x].push_back({y,w});
  }
  sort(gold, gold+n);
  ll mx = 0;
  for(int i = 1; i <= coorx.size(); i++){
    seg SS(3005);
    for(int j = i; j <= coorx.size(); j++){
      for(auto elem : gg[j]){
        SS.add(elem.X, elem.Y);
      }
      //cout << i << ' ' << j << ' ' << SS.get() << "\n";
      //if(i==3 and j==7){
      //  for(int k = 1; k <= 10; k++) cout << SS.d[k] << '\n';
      //}
      mx = max(mx, SS.get());
    }    
  }
  cout << mx;  
}
