#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define X first
#define Y second
#define pb push_back

#define x real() // DO NOT USE x/y as variable!!!!
#define y imag()

typedef long double ld;
const ld e = 1e-9;
typedef complex<ld> pt; // complex<ll> is allowed in GCC
struct cir {
  pt c;
  ld r;
};
int diff(ld l, ld r) {
  if ( abs(l-r) < e) return 0;
  return (l < r) ? -1 : 1;
}
// v가 (e1,e2) line 위에 있을 때 (e1, e2) segment 위에 있는지 판단
bool btn(ld v, ld a, ld b) { // between
  return (min(a,b) - e < v and v < max(a,b) + e);
}
bool pt_btn(pt v, pt e1, pt e2){
  return btn(v.x, e1.x, e2.x) and btn(v.y, e1.y, e2.y);
}
struct line { // st : start point, dir : direction vector. if line is seg, st+dir = end point
  pt st, dir;
};
ld inner(pt a, pt b) {
  return a.x * b.x + a.y * b.y;
}
ld outer(pt a, pt b) {
  return a.x * b.y - a.y * b.x;
}
ld triarea(pt a, pt b, pt c){
  return (ld)0.5*abs(a.x*b.y+b.x*c.y+c.x*a.y-b.x*a.y-c.x*b.y-a.x*c.y);
}
int ccw_line(line l, pt p) {
  return diff(outer(l.dir, p - l.st), 0);
}
int ccw(pt a, pt b, pt c) {
  return diff(outer(b - a, c - a), 0);
}
ld dist(pt a, pt b) {
  return sqrt(inner(a - b, a - b));
}
ld dist2(pt a, pt b) {
  return inner(a - b, a - b);
}
ld dist(line l, pt p, bool seg) {
  ld c1 = inner(p - l.st, l.dir);
  if (seg and diff(c1, 0) <= 0) return dist(l.st, p);
  ld c2 = inner(l.dir, l.dir);
  if (seg && diff(c2, c1) <= 0) return dist(l.st + l.dir, p);
  return dist(l.st + l.dir * (c1 / c2), p);
}
// 0 : not intersect, 1 : intersect in one dot, 2 : intersect in infinite dot
// a나 b가 점일 경우 오작동함. 해당 경우는 따로 예외처리
int line_inter(line a, line b, pt& ret) { 
  ld mdet = outer(b.dir, a.dir);
  if (diff(mdet, 0) == 0){ // parallel
    if(diff(triarea(a.st,a.st+a.dir,b.st),0) == 0 ){ // same line
      ret = a.st;
      return 2;
    }
    return 0;
  }  
  ld t2 = outer(a.dir, b.st - a.st) / mdet;
  ret = b.st + b.dir * t2;
  return 1;
}
// 0 : not intersect, 1 : intersect in one dot, 2 : inter sect in infinite dot
// a나 b가 점일 경우 오작동함. 해당 경우는 따로 예외처리
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

int cmp1(pt a, pt b){
  if(a.x != b.x) return a.x < b.x;
  return a.y < b.y;
}
pt base;
int cmp2(pt a, pt b){
  int cc = ccw(base,a,b);
  return cc >0 or (cc==0 and cmp1(a,b));
}
int n,m;
pt a[105],b[105];
pt c1,c2; 
int main(void){
  //ios::sync_with_stdio(0);
  //cin.tie(0);
  cout << fixed;
  cout.precision(20);
  cin>>n>>m;
  ld cx = 0, cy=0;
  for(int i = 0; i < n; i++){
    ld q,w;
    cin>>q>>w;
    a[i] = {q,w};
    cx+=q; cy+=w;
  }
  for(int i = 0; i < n; i++){
    int ni = (i+1)%n;
    int nii = (i+2)%n;
    //assert(triarea(a[i],a[ni],a[nii])!=0);
  }
  c1 = {cx/n,cy/n};
  cx=0,cy=0;
  for(int i = 0; i < m; i++){
    ld q,w;
    cin>>q>>w;
    b[i] = {q,w};
    cx+=q; cy+=w;
  }
  c2 = {cx/m,cy/m};
  vector<pt> poly;
  for(int i = 0; i < n; i++){
    line l1 = {a[i], c2-a[i]};
    bool inside = 1;
    for(int j = 0; j < m; j++){
      line l2 = {b[j], b[(j+1)%m]-b[j]};
      pt tmp;
      int val = seg_inter(l1,l2,tmp);
      assert(val != 2);
      if(val == 1){
        inside = 0;
        break;
      }
    }
    if(inside) poly.pb(a[i]);
  }
  bool debug = 0;
  if(poly.size()==n) debug = 1;

  for(int i = 0; i < m; i++){
    line l1 = {b[i], c1-b[i]};
    bool inside = 1;
    for(int j = 0; j < n; j++){
      line l2 = {a[j], a[(j+1)%n]-a[j]};
      pt tmp;
      int val = seg_inter(l1,l2,tmp);
      assert(val != 2);
      if(val == 1){
        inside = 0;
        break;
      }      
    }
    if(inside) poly.pb(b[i]);
  }
  for(int i = 0; i < n; i++){
    line l1 = {a[i], a[(i+1)%n]-a[i]};
    for(int j = 0; j < m; j++){
//      assert(triarea(a[i],a[(i+1)%n],b[j]) != 0 or !pt_btn(b[j], a[i],a[(i+1)%n]));
//      assert(triarea(b[j],b[(j+1)%m],a[i]) != 0 or !pt_btn(a[i], b[j], b[(j+1)%m]));      
      line l2 = {b[j], b[(j+1)%m]-b[j]};
      pt tmp;
      int val = seg_inter(l1,l2,tmp);
      assert(val != 2);
      if(val == 1) poly.pb(tmp);
    }
  }
  if(poly.size()<=2){
    cout << 0;
    return 0;
  }
  if(debug){
    assert(n==poly.size());
  }
  //swap(poly[0], *min_element(poly.begin(),poly.end(),cmp1));
  sort(poly.begin(),poly.end(),cmp1);
  base =poly[0];
  sort(poly.begin() + 1, poly.end(),cmp2);
  vector<pt> ch(poly.size());
  int chnum = 0;
  for(int i = 0; i < poly.size(); i++){
    while(chnum > 1 and ccw(ch[chnum-2],ch[chnum-1],poly[i]) <= 0) chnum--;
    ch[chnum++] = poly[i];
  }
  ch.resize(chnum);
  poly = ch;
  ld s = 0;
  for(int i = 0; i < poly.size(); i++){
    s += poly[i].x * poly[(i+1)%poly.size()].y - poly[i].y*poly[(i+1)%poly.size()].x;
  }
  if(s < 0) s = -s;
  cout << s/2;
}
