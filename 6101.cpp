#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pll;
typedef pair<int,int> pii;
#define X first
#define Y second
#define pb push_back

int n,m;
int p[40003];
int cnt[40003];
int d[40003];
int idx[40003][201];
int main(){
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> n >> m;
  for(int i = 1; i <= n; i++) cin >> p[i];
  for(int sz = 1; sz <= 200; sz++){
    fill(cnt,cnt+m+1,0);
    int st= 1, en = 1;
    int diff = 1;
    cnt[p[1]]++;
    while(en <= n and diff < sz){
      en++;
      if(cnt[p[en]] == 0) diff++;
      cnt[p[en]]++;
    }
    if(en==n+1) break;
    while(true){
      while(en <= n and diff == sz){
//        printf("st : %d, en : %d")
        idx[en][sz] = st;
        en++;
        if(cnt[p[en]] == 0) diff++;
        cnt[p[en]]++;
      }
      if(en == n+1) break;
      while(diff == sz+1){
        if(cnt[p[st]] == 1) diff--;
        cnt[p[st]]--;
        st++;
      }
    }
  }
  fill(d+2,d+40001,0x3f3f3f3f);  
  d[1] = 1;
  for(int i = 2; i <= n; i++){
    for(int sz = 1; sz <= 200; sz++){
      if(idx[i][sz] == 0) break;
      //printf("idx[%d][%d] = %d\n",i,sz,idx[i][sz]);
      d[i] = min(d[i],d[idx[i][sz]-1]+sz*sz);
    }
  }
  cout << d[n];
}
