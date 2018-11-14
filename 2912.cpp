#include<bits/stdc++.h>
using namespace std;
#define X first
#define Y second
#define pb push_back
typedef long long ll;

int n,c;
pair<int,int> bb[300300];
int color[300300];
int seg[1201200];
void construct(int node, int nl, int nr){
  if(nl == nr){
    seg[node] = color[nl];
    return;
  }
  int mid = (nl+nr)/2;
  construct(2*node,nl,mid);
  construct(2*node+1,mid+1,nr);
  int cc = seg[2*node];
  int cnt = upper_bound(bb,bb+n,make_pair(cc,nr))-lower_bound(bb,bb+n,make_pair(cc,nl));
  if(cnt > (nr-nl+1)/2){
    seg[node] = cc;
    return;
  }
  cc = seg[2*node+1];
  cnt = upper_bound(bb,bb+n,make_pair(cc,nr))-lower_bound(bb,bb+n,make_pair(cc,nl));
  if(cnt > (nr-nl+1)/2){
    seg[node] = cc;
    return;
  }
  seg[node] = -1;
}
int query(int a, int b, int node, int nl, int nr){
  if(a > nr or b < nl) return -1;
  if(a <= nl and nr <= b){
    int cnt = upper_bound(bb,bb+n,make_pair(seg[node],b))-lower_bound(bb,bb+n,make_pair(seg[node],a));
    if(cnt > (b-a+1)/2) return seg[node];
    else return -1;      
  }
  int mid = (nl+nr)/2;
  int r1 = query(a,b,2*node,nl,mid);
  if(r1 != -1) return r1;
  int r2 = query(a,b,2*node+1,mid+1,nr);
  if(r2 != -1) return r2;
  return -1;
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> n >> c;
  for(int i = 1; i <= n; i++){
    cin >> color[i];
    bb[i-1] = {color[i],i}; 
  } 
  sort(bb,bb+n);
  construct(1,1,n);
  int m;
  cin >> m;
  while(m--){
    int a,b;
    cin >> a >> b;
    int ret = query(a,b,1,1,n);
    if(ret == -1) cout << "no\n";
    else cout << "yes " << ret << '\n';
  }
  
}
