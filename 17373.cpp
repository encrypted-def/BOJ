#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define pb push_back
#define X first
#define Y second
typedef pair<int,int> pii;

// n이 삽입의 최대 횟수일 때 메모리는 최대 (4+lg n)*n만큼 필요. 편의상 25로 두었으나 필요에 따라 조정.
class PST { // 1-indexed node
public:
  int n, nsz = 1;
  vector<int> l, r, val, head;
  PST(int n):n(n),l(25*n+1),r(25*n+1),val(25*n+1), head(n+1){}

  // head가 hidx인 트리의 idx번째에 x를 더할 예정, 그냥 원래 트리 안에서 수정
  void update(int hidx, int idx, int x){
    if(head[hidx] == 0){
      head[hidx] = nsz;
      nsz++;
    }
    val[head[hidx]] += x;
    int cur = head[hidx], st = 1, en = n;
    while(st < en){
      int mid = (st+en)/2;
      if(idx <= mid){ // left tree로 감
        if(l[cur] == 0) l[cur] = nsz++;
        cur = l[cur];
        val[cur] += x;
        en = mid;
      }
      else{
        if(r[cur] == 0) r[cur] = nsz++;
        cur = r[cur];
        val[cur] += x;
        st = mid+1;
      }
    }
  }
  // head가 hidx인 트리의 idx번째에 x를 더할 예정. head가 anc인 트리로부터 가져옴
  void update(int anc, int hidx, int idx, int x){
    val[nsz] = val[head[anc]]+x, l[nsz] = l[head[anc]], r[nsz] = r[head[anc]];
    head[hidx] = nsz;
    nsz++;
    int st = 1;
    int en = n;
    int cur = head[hidx];
    while(st < en){
      int mid = (st+en)/2;
      if(idx <= mid){ // left tree로 감
        val[nsz] = val[l[cur]]+x, l[nsz] = l[l[cur]], r[nsz] = r[l[cur]];
        l[cur] = nsz++;
        cur = l[cur];
        en = mid;
      }
      else{
        val[nsz] = val[r[cur]]+x, l[nsz] = l[r[cur]], r[nsz] = r[r[cur]];
        r[cur] = nsz++;
        cur = r[cur];
        st = mid+1;
      }
    }
  }
  int query(int i, int j, int node, int nl, int nr){
    if(j < nl or i > nr) return 0;
    if(i <= nl and nr <= j) return val[node];
    int mid = (nl+nr)/2;
    return query(i,j,l[node],nl,mid)+query(i,j,r[node],mid+1,nr);
  }
  // head[hidx]에서 i-th ~ j-th element의 합
  int query(int hidx, int i, int j){
    return query(i, j, head[hidx], 1, n);
  }
  int query2(int node, int cnt, int nl, int nr){
    //printf("now cnt : %d\n",cnt);
    if(nl==nr) return nl;
    if(val[l[node]] >= cnt) return query2(l[node], cnt, nl, (nl+nr)/2);
    else return query2(r[node], cnt-val[l[node]], (nl+nr)/2+1, nr);
  }
  // head[hidx]에서 i번째 1이 무엇인지
  int query2(int hidx, int cnt){
    return query2(head[hidx], cnt, 1, n);
  }
};

int n,m,q;
int novel[100001];
ll p[1000001]; // 각 글자에 대해 사용가능한 문자의 갯수
ll psum[1000001];
bool occur[1000001]; // 시작 위치
bool occur2[1000001]; // pst에 넣을지말지 결정하기 위한 것.(오른쪽에서 왼쪽)
bool mark[1000001]; // 해당 칸이 시작 위치인지
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> n >> m >> q;
  stack<int> S;
  PST pst(1000001);
  for(int i = 0; i < n; i++){
    cin >> novel[i];
    if(!occur[novel[i]]){
      S.push(novel[i]);
      occur[novel[i]] = true;
      mark[i] = 1;
    }
  }
  for(int i = 1; i <= m; i++)
    pst.update(S.top(), i, 1);

  for(int i = n-1; i >= 1; i--){
    if(mark[i]){
      S.pop();
      pst.update(novel[i], S.top(), 1, 0); // 그냥 값 변경은 없이 copy하는 것으로 생각하면 됨
      p[novel[i]] = pst.query(novel[i], 1, m);
    }
    if(!occur2[novel[i]]){
      pst.update(S.top(), S.top(), novel[i], -1);
      occur2[novel[i]] = true;
    }
  }
  p[novel[0]] = pst.query(novel[0], 1, m);
  for(int i = 1; i <= m; i++){
    if(!occur[i])
      p[i] = m;
    psum[i] = psum[i-1]+p[i];
  }
  while(q--){
    ll k;
    cin >> k;
    if(k > psum[m]){
      cout << "-1 -1\n";
      continue;
    }
    int fst = 1;
    int fen = m;
    while(fst < fen){
      int mid = (fst+fen)/2;
      if(psum[mid] < k)
        fst = mid+1;
      else
        fen = mid;
    }
    cout << fst << ' ';
    if(p[fst] == m) cout << k-psum[fst-1] << '\n';
    else{
      cout << pst.query2(fst, k-psum[fst-1]) << '\n';
    }
  }
}
