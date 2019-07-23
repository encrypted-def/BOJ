#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define X first
#define Y second
typedef pair<int,int> pii;
char board[1005][1005];
int n,m;

int dx[8] = {1,1,1,0,0,-1,-1,-1};
int dy[8] = {1,0,-1,1,-1,1,0,-1};
bool vis[1005][1005];
int chk(int x, int y){
  int cnt = 0;
  for(int dir = 0; dir < 8; dir++){
    if(board[x+dx[dir]][y+dy[dir]] == '.') cnt++;
  }
  return cnt;
}
int main(){
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> n >> m;
  int cnt = 0;
  vector<pii> sand;
  for(int i = 0; i < n; i++){
    cin >> board[i];
  }
  for(int i = 0; i < n; i++){
    for(int j = 0; j < m; j++){
      if(board[i][j] != '.' and chk(i,j) >= board[i][j]-'0'){
        sand.pb({i,j});
        vis[i][j]=1;
      }
    }
  }
  int ans = 0;
  while(!sand.empty()){
    ans++;
    vector<pii> sand2;
    for(auto s : sand){
      board[s.X][s.Y] = '.';
    }
    for(auto s : sand){
      int x = s.X, y = s.Y;
      for(int dir = 0; dir < 8; dir++){
        int nx = x+dx[dir];
        int ny = y+dy[dir];
        if(!vis[nx][ny] and board[nx][ny] != '.' and chk(nx,ny) >= board[nx][ny]-'0'){
          sand2.pb({nx,ny});
          vis[nx][ny] = 1;
        }
      }
    }
    sand = sand2;
  }
  cout << ans;
  
}
