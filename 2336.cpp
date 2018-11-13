#include<bits/stdc++.h>
using namespace std;
#define X first
#define Y second
#define pb push_back
typedef long long ll;



class Seg { // 0-indexed
public:
  int n;
  vector<ll> a;
  Seg(int n) : n(n), a(2*n, 0x7f7f7f) {}
  void init() {
    for (int i = n - 1; i > 0; i--) a[i] = min(a[i << 1], a[i << 1|1]);
  }
  void update(int i, ll val) { // change i-th element to val(0-indexed)
    for (a[i += n] = val; i > 1; i >>= 1) a[i >> 1] = min(a[i], a[i ^ 1]);
  }
  // sum of l-th to r-th element(0-indexed)
  ll query(int l, int r) {
    ll ret = 0x7f7f7f;
    for (l += n, r += n+1; l < r; l >>= 1, r >>= 1) {
      if (l & 1) ret = min(ret,a[l++]);
      if (r & 1) ret = min(ret,a[--r]);
    }
    return ret;
  }
  void pushval(int i, ll val){ // set i-th element to val
    a[i+n]=val;
  }
};
int n;
int r[3][500003];
int ord[3][500003];
int cnt = 0;
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> n;
  for(int i = 0; i < 3; i++){
    for(int j = 1; j <= n; j++){
      cin >> r[i][j];
      ord[i][r[i][j]] = j;
    }
  }
  Seg S(n+10);
  for(int i = 1; i <= n; i++){
    int user = r[0][i];
    int r1 = ord[1][user];
    int r2 = ord[2][user];
    if(S.query(1,r1) > r2) cnt++;
    S.update(r1, r2);
  }
  cout << cnt;
}
