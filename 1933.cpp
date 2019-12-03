#include <bits/stdc++.h>
using namespace std;
#define pb push_back
typedef long long ll;
#define X first
#define Y second
int n;
tuple<int,int,int> b[100005];

vector<pair<int,int>> schedule;

int main(){
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> n;
  for(int i = 0; i < n; i++){
    int l,h,r;
    cin>>l>>h>>r;
    schedule.pb({l,h});
    schedule.pb({r,-h});
  }
  sort(schedule.begin(),schedule.end());
  schedule.pb({0x7f7f7f7f,0x7f7f7f7f});
  multiset<int> S;
  S.insert(0);
  int beforex = schedule[0].X;
  int beforey = -1;
  int i = 0;
  while(i < 2*n){
    while(beforex == schedule[i].X){
      int x = schedule[i].X;
      int h = schedule[i].Y;
      if(h < 0) S.erase(S.find(-h));
      else S.insert(h);
      i++;
    }
    int val = *prev(S.end());
    if(val != beforey){
      cout << beforex << ' ' << *prev(S.end()) << ' ';
      beforey = val;
    }
    beforex = schedule[i].X;
  }


  

}

