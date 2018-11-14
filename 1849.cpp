#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define X first
#define Y second
#define pb push_back
int seg[400005];
void upd(int i, int val, int node, int nl, int nr){
  if(i < nl or i > nr) return;
  if(nl == nr){
    seg[node] = val;
    return;
  }
  int mid = (nl+nr)/2;
  upd(i,val,2*node,nl,mid);
  upd(i,val,2*node+1,mid+1,nr);
  seg[node] = seg[2*node]+seg[2*node+1];
}
int sum(int i, int j, int node, int nl, int nr){
  if(j < nl or i > nr) return 0;
  if(i <= nl and nr <= j) return seg[node];
  int mid = (nl+nr)/2;
  return sum(i,j,2*node,nl,mid)+sum(i,j,2*node+1,mid+1,nr);
}
int kth(int i, int node, int nl, int nr){
  if(nl == nr) return 1;
  int mid = (nl+nr)/2;
  if(seg[2*node] >= i) return kth(i,2*node,nl,mid);
  else return (mid-nl+1)+kth(i-seg[2*node],2*node+1,mid+1,nr);
}

int main(void){
  ios::sync_with_stdio(0);
  cin.tie(0);
  int n;
  int ord[100004];
  int ans[100004];
  cin >> n;
  for(int i = 1; i <= n; i++) upd(i,1,1,1,n);
  for(int i = 1; i <= n; i++){
    int t;
    cin >> t;
    int kk = kth(t+1,1,1,n);
    ans[kk] = i;
    upd(kk,0,1,1,n);
  }
  for(int i = 1; i <= n ; i++) cout << ans[i] << '\n';
}
