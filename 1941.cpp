#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define X first
#define Y second
#define pb push_back
int dx[4] = {1,-1,0,0};
int dy[4] = {0,0,1,-1};
char s[6][6];
int main(void){
  ios::sync_with_stdio(0);
  cin.tie(0);
  for(int i = 0; i < 5; i++) cin>> s[i];
  vector<bool> brute(25);
  for(int i = 18; i < 25; i++) brute[i]=1;
  int tot = 0;
  do{
    vector<bool> vis(25);
    int st = 0;
    while(!brute[st]) st++;
    int x = st/5;
    int y = st%5;
    queue<int> Q;
    Q.push(st);
    vis[st]=1;
    int cnt1 = 0,cnt2=0;
    while(!Q.empty()){
      int cur = Q.front(); Q.pop();
      int cx = cur/5; int cy = cur%5;
      if(s[cx][cy]=='S')cnt1++;
      else cnt2++;
      for(int dir = 0; dir < 4; dir++){
        int nx = cx+dx[dir];
        int ny = cy+dy[dir];
        if(0>nx or 0>ny or 4<nx or 4<ny) continue;
        if(vis[5*nx+ny]) continue;
        if(!brute[5*nx+ny]) continue;
        Q.push(5*nx+ny);
        vis[5*nx+ny]=1;
      }
    }
    if(cnt1+cnt2==7 and cnt1 >= 4) tot++;
    //cout << cnt1 << ' ' << cnt2<<'\n';

  }while(next_permutation(brute.begin(),brute.end()));
  cout <<tot;
}
