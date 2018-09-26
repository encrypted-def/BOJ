#include <bits/stdc++.h>
using namespace std;
int N,X0,A,B,M;
int q[1001],st[1001],en[1001],mid[1001];
const int MOD = 1e9+7;
int main(void){
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin>>N>>X0>>A>>B>>M;
  for(int i = 0; i < M; i++){
    cin >> q[i];
    q[i]++;
    st[i] = 0;
    en[i] = MOD-1;
    mid[i] = (st[i]+en[i])>>1;
  }
  sort(q,q+M);
  int isDone = 0;
  while(!isDone){
    int delta[M+1] = {0,};
    isDone = 1;
    int arr = X0;
    for(int i = 0; i < N; i++){
      int r = lower_bound(mid,mid+M,arr)-mid;
      delta[r]++;
      arr = (1ll*arr*A+B)%MOD;
    }
    int cnt = 0;
    for(int i = 0; i < M; i++){
      cnt += delta[i];
      if(st[i] == en[i]) continue;
      if(cnt > q[i])
        en[i] = mid[i]-1;
      else if(cnt == q[i])
        en[i] = mid[i];
      else
        st[i] = mid[i]+1;
      mid[i] = (st[i]+en[i])>>1;
      if(st[i] != en[i]) isDone = 0;
    }
  }
  long long tot = 0;
  for(int i = 0; i < M; i++){
    tot += st[i];
  }
  cout << tot;


}
