#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define X first
#define Y second
#define pb push_back

int main(void){
  ios::sync_with_stdio(0);
  cin.tie(0);
  int n;
  cin >> n;
  while(n--){
    int k;
    cin>>k;
    if(__builtin_popcount(k) == 1) cout << "GoHanGang\n";
    else cout << "Gazua\n";
  }
}
