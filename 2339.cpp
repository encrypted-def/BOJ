#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define X first
#define Y second
#define pb push_back
int n;
int board[21][21];
int d[21][21][21][21][2]; // 0 : 가로로 자름, 1 : 세로로 자름
int cut0[21][21][21]; // cut0[a][b][c] : board[a][b~c]로 자를 수 있는지(=결정체가 있는지)
int cut1[21][21][21]; // board[b~c][a] @@@
int num_jw[21][21];
int num_dust[21][21];


int dust(int x1, int x2, int y1, int y2){
  return num_dust[x2][y2]-num_dust[x1-1][y2]-num_dust[x2][y1-1]+num_dust[x1-1][y1-1];
}
int jw(int x1, int x2, int y1, int y2){
  return num_jw[x2][y2]-num_jw[x1-1][y2]-num_jw[x2][y1-1]+num_jw[x1-1][y1-1];
}

int solve(int x1, int x2, int y1, int y2, int dir){
  int& val = d[x1][x2][y1][y2][dir];
  if(val != -1) return val;
  if(jw(x1,x2,y1,y2)==0){
    return val = 0;
  }
  if(jw(x1,x2,y1,y2)==1){
    if(dust(x1,x2,y1,y2) > 0) val = 0;
    else val = 1;
    return val;
  }
  val = 0;
  if(dir == 0){
    for(int div = x1+1; div < x2; div++){
      if(cut0[div][y1][y2]){        
        val += solve(x1,div-1,y1,y2,1)*solve(div+1,x2,y1,y2,1);
      }
    }
    return val;
  }
  else{
    for(int div = y1+1; div < y2; div++){
      if(cut1[div][x1][x2]){
        val += solve(x1,x2,y1,div-1,0)*solve(x1,x2,div+1,y2,0);
      }
    }
    return val;
  }
  assert(0);
  return -1; // unreachable
}
int main(void){
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin>>n;
  for(int i = 1; i <= n; i++){
    for(int j = 1; j <= n; j++){
      cin>>board[i][j];
    }
  }
  for(int i = 1; i <= n; i++){
    for(int j = 1; j <= n; j++){
      bool cut_jw = 0, cut_dust = 0;
      for(int k = j; k <= n; k++){
        cut_jw = cut_jw or (board[i][k]==2);
        cut_dust = cut_dust or (board[i][k]==1);
        cut0[i][j][k] = !cut_jw and cut_dust;
      }
    }
  }
  for(int i = 1; i <= n; i++){
    for(int j = 1; j <= n; j++){
      bool cut_jw = 0, cut_dust = 0;
      for(int k = j; k <= n; k++){
        cut_jw = cut_jw or (board[k][i]==2);
        cut_dust = cut_dust or (board[k][i]==1);
        cut1[i][j][k] = !cut_jw and cut_dust;
      }
    }
  }
  for(int i = 1; i <= n; i++){
    num_jw[1][i] = num_jw[1][i-1]+(board[1][i]==2);
    num_dust[1][i] = num_dust[1][i-1]+(board[1][i]==1);
  }
  for(int i = 2; i <= n; i++){
    for(int j = 1; j <= n; j++){
      num_jw[i][j] = num_jw[i-1][j]+num_jw[i][j-1]-num_jw[i-1][j-1]+(board[i][j]==2);
      num_dust[i][j] = num_dust[i-1][j]+num_dust[i][j-1]-num_dust[i-1][j-1]+(board[i][j]==1);
    }
  }
  memset(d,-1,sizeof(d));
  //cout << jw(1,n,1,n);
  int ans = solve(1,n,1,n,0) + solve(1,n,1,n,1);
  if(ans==0)ans=-1;
  cout << ans;
}
