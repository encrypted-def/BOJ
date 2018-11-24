#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define X first
#define Y second
#define pb push_back
#define x real()
#define y imag()
typedef long double ld;
const ld e = 1e-9;

typedef complex<ld> pt;
struct line{
  pt st,dir;
};

int diff(ld l, ld r){
  if(abs(l-r)<e) return 0;
  return (l<r) ? -1 : 1;
}
bool btn(ld v, ld a, ld b){
  return (min(a,b)-e < v and v < max(a,b)+e);
}

// v가 (e1,e2) line 위에 있을 때 (e1, e2) segment 위에 있는지 판단
bool pt_btn(pt v, pt e1, pt e2){
  return btn(v.x, e1.x, e2.x) and btn(v.y, e1.y, e2.y);
}


ld outer(pt a, pt b){
  return a.x *b.y-a.y*b.x;
}
ld triarea(pt a, pt b, pt c){
  return (ld)0.5*abs(a.x*b.y+b.x*c.y+c.x*a.y-b.x*a.y-c.x*b.y-a.x*c.y);
}
int seg_inter(line a, line b, pt& ret) {
  ld mdet = outer(b.dir, a.dir);
  if (diff(mdet, 0) == 0){ // parallel
    if(diff(triarea(a.st,a.st+a.dir,b.st),0) == 0 ){ // same line
      if(pt_btn(a.st,b.st,b.st+b.dir)){
        ret = a.st;
        return 2;
      }
      if(pt_btn(a.st+a.dir,b.st,b.st+b.dir)){
        ret = a.st+a.dir;
        return 2;
      }
      if(pt_btn(b.st,a.st,a.st+a.dir)){
        ret = b.st;
        return 2;
      }
      if(pt_btn(b.st+b.dir,a.st,a.st+a.dir)){
        ret = b.st+b.dir;
        return 2;
      }
      return 0;
    }
    return 0;
  }
  ld t1 = -outer(b.st - a.st, b.dir) / mdet;
  ld t2 = outer(a.dir, b.st - a.st) / mdet;
  if (!btn(t1, 0, 1) or !btn(t2, 0, 1)) return 0;
  ret = b.st + b.dir * t2;
  return 1;
}
int n;
pt a[15];
pt b[15];
int inter[15][15][15][15];
int main(void){
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> n;
  for(int i = 0; i < n; i++){
    ld q,w;
    cin>>q>>w;
    a[i] = {q,w};
  }
  for(int i = 0; i < n; i++){
    ld q,w;
    cin>>q>>w;
    b[i] = {q,w};
  }
  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      if(i==j) continue;
      for(int k = 0; k < n; k++){
        for(int l = 0; l < n; l++){
          if(k==l) continue;
          line l1,l2;
          l1.st = a[i];
          l1.dir = b[k]-a[i];
          l2.st = a[j];
          l2.dir = b[l]-a[j];
          pt tmp;
          inter[i][j][k][l] = seg_inter(l1,l2,tmp);
        }
      }
    }
  }
  int brute[n];
  for(int i = 0; i < n; i++) brute[i] = i;
  do{
    bool pos = 1;
    for(int i = 0; i < n; i++){
      if(!pos) break;
      for(int j = i+1; j < n; j++){
        if(inter[i][j][brute[i]][brute[j]]){
          pos = 0;
          break;
        }
      }
    }
    if(pos){
      for(int i = 0; i < n; i++) cout << brute[i]+1 << '\n';
      return 0;
    }

  }while(next_permutation(brute,brute+n));
  assert(0);

}
