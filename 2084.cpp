#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define X first
#define Y second
#define pb push_back
int a[2003][2003];
int main(void){
  ios::sync_with_stdio(0);
  cin.tie(0);
  int n;
  cin >> n;
  pair<int,int> v[n];
  int tot = 0;
  for(int i = 0; i < n; i++){
    cin >> v[i].X;
    tot += v[i].X;
    v[i].Y = i;
  }
  if(tot%2==1){
    cout << -1;
    return 0;
  }
  while(true){
    sort(v,v+n,greater<pair<int,int> >() );
    if(v[0].X == 0) break;
    int cnt = v[0].X;
    v[0].X = 0;
    int i = 1;
    while(cnt){
      if(i==n){
        cout << -1;
        return 0;
      }
      if(a[v[0].Y][v[i].Y]){
        i++;
        continue;
      }
      a[v[0].Y][v[i].Y] = a[v[i].Y][v[0].Y] = 1;
      v[i].X--;
      i++;
      cnt--;
    }
  }
  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++) cout << a[i][j] << ' ';
    cout << '\n';
  }

}
