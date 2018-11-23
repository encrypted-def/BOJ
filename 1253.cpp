#include<bits/stdc++.h>
using namespace std;
#define X first
#define Y second
#define pb push_back
typedef long long ll;

int n;
int a[2004];
map<int,int> occur;
vector<int> add;
int main(void){
  ios::sync_with_stdio(0);
  cin.tie(0);
  int n;
  cin >> n;
  for(int i = 0; i < n; i++){
    cin >> a[i];
    occur[a[i]] += 1;
  }
  for(int i = 0; i < n; i++){
    if(a[i] == 0) continue;
    for(int j = i+1; j < n; j++){
      if(a[j] == 0) continue;
      add.pb(a[i]+a[j]);
    }
  }
  sort(add.begin(),add.end());
  int cnt = 0;
  for(int i = 0; i < n; i++){
    if(binary_search(add.begin(),add.end(),a[i])){
      cnt++;
      continue;
    }
    if(a[i] == 0){
      if(occur[0] >= 3){
        cnt++;
      }
      continue;
    }
    if(occur[0] >= 1 and occur[a[i]] >= 2){
      cnt++;
    }

  }
  cout << cnt;

}
