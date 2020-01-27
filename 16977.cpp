#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define X first
#define Y second
using ll = long long;
using ti3 = tuple<int,int,int>;
class PST { // 1-indexed node
public:
  // lmax : 제일 왼쪽 원소 포함, rmax : 제일 오른쪽 원소 포함
  class Node{
    public:
    int l, r, val, lmax, rmax, allmax;
  };
  int n, nsz = 1;
  vector<int> head;
  vector<Node> node;
  PST(int n):n(n),node(25*n+1), head(n+10){}
  void _upd1(int i, int nidx, int nl, int nr){
    if(nl == nr){
      node[nidx].val = node[nidx].lmax = node[nidx].rmax = node[nidx].allmax = 1;
      return;
    }
    int mid = (nl+nr)/2;
    if(i <= mid){
      if(!node[nidx].l) node[nidx].l = nsz++;
      _upd1(i, node[nidx].l, nl, mid);
    }
    else{
      if(!node[nidx].r) node[nidx].r = nsz++;
      _upd1(i, node[nidx].r, mid+1, nr);
    }
    int lidx = node[nidx].l;
    int ridx = node[nidx].r;
    
    node[nidx].lmax = node[lidx].lmax;
    if(node[lidx].lmax == mid-nl+1)
      node[nidx].lmax += node[ridx].lmax;
    
    node[nidx].rmax = node[ridx].rmax;
    if(node[ridx].rmax == nr-mid)
      node[nidx].rmax += node[lidx].rmax;

    node[nidx].allmax = max({node[nidx].lmax, node[nidx].rmax, node[lidx].allmax, node[ridx].allmax, node[lidx].rmax+node[ridx].lmax});
    node[nidx].val = 1;
  }  
  // head가 hidx인 트리의 i번째를 0에서 1로 만듬, 그냥 원래 트리 안에서 수정하니 ***맨 처음의 트리를 생성할 때만*** 사용해야 함
  void update1(int hidx, int i, int x){
    if(head[hidx] == 0){
      head[hidx] = nsz;
      nsz++;
    }
    // 트리의 좌우 범위가 1 to n이 아닐 수도 있으니 상황에 맞게 조정
    _upd1(i, head[hidx], 1, n);
  }
  void _upd2(int i, int nidx, int nl, int nr){    
    if(nl == nr){
      node[nidx].val = node[nidx].lmax = node[nidx].rmax = node[nidx].allmax = 1;
      return;
    }
    int mid = (nl+nr)/2;
    if(i <= mid){
      node[nsz] = node[node[nidx].l];
      node[nidx].l = nsz++;
      _upd2(i, node[nidx].l, nl, mid);
    }
    else{
      node[nsz] = node[node[nidx].r];
      node[nidx].r = nsz++;
      _upd2(i,node[nidx].r, mid+1, nr);
    }

    int lidx = node[nidx].l;
    int ridx = node[nidx].r;
    
    node[nidx].lmax = node[lidx].lmax;
    if(node[lidx].lmax == mid-nl+1)
      node[nidx].lmax += node[ridx].lmax;
    
    node[nidx].rmax = node[ridx].rmax;
    if(node[ridx].rmax == nr-mid)
      node[nidx].rmax += node[lidx].rmax;

    node[nidx].allmax = max({node[nidx].lmax, node[nidx].rmax, node[lidx].allmax, node[ridx].allmax, node[lidx].rmax+node[ridx].lmax});
    node[nidx].val = 1;    
  }
  // head가 hidx인 트리의 idx번째에 x를 더할 예정. head가 anc인 트리로부터 가져옴
  // 이미 트리 간의 서로 참조가 발생한 후에 특정 트리 내의 값을 바꾸고 싶으면 update1(hidx, i, x) 대신 update2(hidx, hidx, i, x)를 호출해야 함
  void update2(int anc, int hidx, int i){
    node[nsz] = node[head[anc]];
    head[hidx] = nsz++;
    // 트리의 좌우 범위가 1 to n이 아닐 수도 있으니 상황에 맞게 조정
    _upd2(i, head[hidx], 1, n);    
  }
  // {lmax, rmax, allmax}
  ti3 query1(int i, int j, int nidx, int nl, int nr){
    //cout << "query1 " << nidx << ' ' << nl << ' ' << nr << "-----\n";
    if(j < nl or i > nr) return {0,0,0};
    //cout << "this1???\n";
    if(i <= nl and nr <= j) return {node[nidx].lmax, node[nidx].rmax, node[nidx].allmax};
    //cout << "this2???\n";    
    int mid = (nl+nr)/2;
    ti3 result1 = query1(i, j, node[nidx].l, nl, mid);
    int lmax1, rmax1, allmax1;
    tie(lmax1, rmax1, allmax1) = result1;
    ti3 result2 = query1(i, j, node[nidx].r, mid+1, nr);
    int lmax2, rmax2, allmax2;
    tie(lmax2, rmax2, allmax2) = result2;

    int lret=0, rret = 0, allret = 0;
    lret = lmax1;
    if(lmax1 == mid-nl+1) lret += lmax2;

    rret = rmax2;
    if(rmax2 == nr-mid) rret += rmax1;

    allret = max({allmax1, allmax2, lret, rret, rmax1+lmax2});
    //cout << "ret ---- " << lret << ' ' << rret << ' ' << allret << '\n';
    return {lret, rret, allret};
  }
  // head[hidx]에서 i-th ~ j-th element에서의 allmax
  int query1(int hidx, int i, int j){
    return get<2>(query1(i, j, head[hidx], 1, n));
  }
  void _debug(int nidx, int nl, int nr){
    cout << "nidx : " << nidx << " range : " << nl << ' ' << nr << ' ' << "val : " << node[nidx].lmax << ' ' << node[nidx].rmax << ' ' << node[nidx].allmax << '\n';
    if(nl == nr) return;
    int mid = (nl+nr)/2;
    _debug(node[nidx].l, nl, mid);
    _debug(node[nidx].r, mid+1, nr);    
  }

  void debug(int hidx){
    _debug(head[hidx],1,n);
  }
};

int n,q;
int h[100005];
vector<int> coorh;
int hrecover[100005];
int idxbyh[100005];
vector<pair<int,int> > horder;
int main(){
  ios::sync_with_stdio(0); cin.tie(0);
  cin >> n;
  fill(idxbyh, idxbyh+100001,-1);
  for(int i = 0; i < n; i++){
    cin >> h[i];
    coorh.pb(h[i]);
    horder.pb({h[i],i});
  }
  coorh.pb(-1);
  sort(coorh.begin(), coorh.end());
  coorh.erase(unique(coorh.begin(),coorh.end()), coorh.end());
  for(int i = 0; i < coorh.size(); i++)
    hrecover[i] = coorh[i];
  PST pst(n);
  sort(horder.begin(),horder.end());
  for(int i = n-1; i >= 0; i--){
    int hh, idx;
    tie(hh, idx) = horder[i];
    idx++;
    hh = lower_bound(coorh.begin(),coorh.end(),hh)-coorh.begin();
    if(idxbyh[hh] == -1) pst.update2(hh+1, hh, idx);
    else pst.update2(hh, hh, idx);
    idxbyh[hh] = idx;
  }
  //pst.debug(3);
  //cout << "-------------------------\n";
  /*pst.debug(1);
  cout << "-------------------------\n";
  pst.debug(2);
  cout << "-------------------------\n";
  pst.debug(3);
  cout << "-------------------------\n";
  pst.debug(4);
  cout << "-------------------------\n";
  pst.debug(5);
  cout << "-------------------------\n";*/

  cin >> q;
  while(q--){
    int l,r,w;
    cin >> l >> r >> w;
    int st = 1, en = coorh.size()-1;
    while(st < en){
      int mid = (st+en+1)/2;
      //cout << mid << ' ' << pst.query1(mid,l,r) << '\n';
      if(pst.query1(mid,l,r) >= w) st = mid;
      else en = mid-1;
    }
    cout << hrecover[st] << '\n';
  }
}
