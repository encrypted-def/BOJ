#include <bits/stdc++.h>
using namespace std;

#define X first
#define Y second
#define pb push_back
typedef long long ll;
typedef unsigned long long ull;
typedef pair <int, int> pii;

int R,C;
int rszR, rszC;
vector<int> allx, ally;
class seg_col{
public:
  class Node{
  public:
    ll val;
    int l, r;
  };
  vector<Node> node; // root : 1
  seg_col():node(2){}
  void upd(int i, ll val, int nidx, int nl, int nr){
    if(i < nl or i > nr) return;
    if(nl == nr){
      node[nidx].val = val;
      return;
    }
    int mid = (nl+nr)/2;
    if(nl <= i and i <= mid){
      if(node[nidx].l == 0){
        node.pb({val,0,0});
        node[nidx].l = node.size()-1;
      }
      upd(i, val, node[nidx].l, nl, mid);
    }
    else{
      if(node[nidx].r == 0){
        node.pb({val,0,0});
        node[nidx].r = node.size()-1;
      }
      upd(i, val, node[nidx].r, mid+1, nr);
    }
    node[nidx].val = __gcd(node[node[nidx].l].val, node[node[nidx].r].val);

  }
  void upd(int i, ll val){
    upd(i, val, 1, 1, rszC);
  }
  ll query(int i, int j, int nidx, int nl, int nr){
    if(j < nl or nr < i) return 0;
    if(i <= nl and nr <= j) return node[nidx].val;
    ll ret = 0;
    int mid = (nl+nr)/2;
    if(node[nidx].l != 0) ret = __gcd(ret, query(i, j, node[nidx].l, nl, mid));
    if(node[nidx].r != 0) ret = __gcd(ret, query(i, j, node[nidx].r, mid+1, nr));
    return ret;    
  }
  ll query(int i, int j){
    return query(i, j, 1, 1, rszC);
  }
};

class seg_row{
public:
  class Node{
  public:
    seg_col tree;
    int l, r;
  };
  vector<Node> node;
  seg_row():node(2){}
  void upd_node(int y, int nidx, int nl, int nr, int curidx, int lidx, int ridx){
    auto& cur_tree = node[nidx].tree;
    auto& left_tree = node[node[nidx].l].tree;
    auto& right_tree = node[node[nidx].r].tree;
    //printf("left idx : %d, right idx : %d\n", node[nidx].l, node[nidx].r);
    cur_tree.node[curidx].val = __gcd(left_tree.node[lidx].val,right_tree.node[ridx].val);
    //printf("upd_node %d, val : %lld(=%lld XOR %lld)\n",nidx,cur_tree.node[curidx].val,left_tree.node[lidx].val,right_tree.node[ridx].val);
    if(nl == nr) return;
    int mid = (nl+nr)/2;
    if(y <= mid){
      if(cur_tree.node[curidx].l == 0){
        cur_tree.node.pb({0,0,0});
        cur_tree.node[curidx].l = cur_tree.node.size()-1;
      }
      curidx = cur_tree.node[curidx].l;
      lidx = left_tree.node[lidx].l;
      ridx = right_tree.node[ridx].l;
      upd_node(y, nidx, nl, mid, curidx, lidx, ridx);
    }
    else{
      if(cur_tree.node[curidx].r == 0){
        cur_tree.node.pb({0,0,0});
        cur_tree.node[curidx].r = cur_tree.node.size()-1;
      }
      curidx = cur_tree.node[curidx].r;
      lidx = left_tree.node[lidx].r;
      ridx = right_tree.node[ridx].r;
      upd_node(y, nidx, mid+1, nr, curidx, lidx, ridx);
    }
  }
  void upd(int x, int y, ll val, int nidx, int nl, int nr){
    if(x < nl or x > nr) return;
    if(nl == nr){
      //printf("upd_leaf : %d(%d~%d)\n",nidx,nl,nr);
      node[nidx].tree.upd(y, val);
      return;
    }
    int mid = (nl+nr)/2;
    if(nl <= x and x <= mid){
      if(node[nidx].l == 0){
        node.pb({seg_col(),0,0});
        node[nidx].l = node.size()-1;
      }
      upd(x, y, val, node[nidx].l, nl, mid);
    }
    else{
      if(node[nidx].r == 0){
        node.pb({seg_col(),0,0});
        node[nidx].r = node.size()-1;
      }
      upd(x, y, val, node[nidx].r, mid+1, nr);
    }
    upd_node(y, nidx, 1, rszC, 1, 1, 1);
  }
  void upd(int x, int y, ll val){
    x = lower_bound(allx.begin(),allx.end(),x)-allx.begin();
    y = lower_bound(ally.begin(),ally.end(),y)-ally.begin();    
    upd(x,y,val,1,1,rszR);
  }
  ll query(int x1, int y1, int x2, int y2, int nidx, int nl, int nr){
    //printf("now nidx %d\n",nidx);
    if(x2 < nl or x1 > nr) return 0;
    if(x1 <= nl and nr <= x2){
      //printf("this %d %d %d %d %d\n",x1,y1,x2,y2,nidx);
      //printf("%lld %lld %lld\n", node[1].tree.node[1].val, node[1].tree.node[2].val, node[1].tree.node[3].val);
      return node[nidx].tree.query(y1,y2);
    }
    ll ret = 0;
    int mid = (nl+nr)/2;
    if(node[nidx].l != 0){
      ret = __gcd(ret, query(x1, y1, x2, y2, node[nidx].l, nl, mid));
    }
    if(node[nidx].r != 0){
      ret = __gcd(ret, query(x1, y1, x2, y2, node[nidx].r, mid+1, nr));
    }
    return ret;
  }
  ll query(int x1, int y1, int x2, int y2){
    x1 = lower_bound(allx.begin(),allx.end(),x1)-allx.begin();
    x2 = lower_bound(allx.begin(),allx.end(),x2)-allx.begin();
    y1 = lower_bound(ally.begin(),ally.end(),y1)-ally.begin();
    y2 = lower_bound(ally.begin(),ally.end(),y2)-ally.begin();
    return query(x1, y1, x2, y2, 1, 1, rszR);
  }
};
typedef tuple<ll,ll,ll,ll,ll> ti5;
vector<ti5> query;
int main(){
  ios::sync_with_stdio(0);
  cin.tie(0);
  int Q;
  cin >> R >> C >> Q;
  query.resize(Q);
  allx.pb(-1);
  ally.pb(-1);
  for(int i = 0; i < Q; i++){
    int q;
    cin >> q;
    if(q==1){
      ll x,y,k;
      cin >> x >> y >> k;
      allx.pb(x);
      ally.pb(y);
      query[i] = {q,x,y,k,-1};
    }
    else{
      int x1,y1,x2,y2;
      cin >> x1 >> y1 >> x2 >> y2;
      allx.pb(x1);
      allx.pb(x2);
      ally.pb(y1);
      ally.pb(y2);
      query[i] = {q,x1,y1,x2,y2};
    }
  }
  sort(allx.begin(),allx.end());
  sort(ally.begin(),ally.end());  
  allx.erase(unique(allx.begin(),allx.end()), allx.end());
  ally.erase(unique(ally.begin(),ally.end()), ally.end());
  rszR = allx.size()-1;
  rszC = ally.size()-1;
  seg_row S;
  for(int i = 0; i < Q; i++){
      //printf("----- query %d ----\n", i+1);

//    cout << i << "th query\n";
    ll q,t1,t2,t3,t4;
    tie(q,t1,t2,t3,t4) = query[i];
    if(q==1)
      S.upd(t1, t2, t3);
    else
      cout << S.query(t1,t2,t3,t4) << '\n';
  }
}
