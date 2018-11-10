#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define X first
#define Y second
#define pb push_back

int n;
pair<ll,ll> original[1501];
ll tot = 0;
void calc(int center){
  map<pair<ll,ll>, int> M;
  int idx = 0;
  for(int i = 0; i < n; i++){
    if(i==center) continue;
    ll tx = original[i].X-original[center].X;
    ll ty = original[i].Y-original[center].Y;
    ll g = __gcd(tx,ty);
    if(g<0) g = -g;
    tx /= g;
    ty /= g;
    M[{tx,ty}]++;
  }
  for(auto elem : M){
    ll x = elem.X.X;
    ll y = elem.X.Y;
//    cout << x << ' ' << y << '\n';
    if(M.find({-y,x}) != M.end()){
      tot += elem.Y * M[{-y,x}];
//      cout << x << ' ' << y << ' ' << tot << endl;
    }
  }
  
}
int main(void){
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> n;
  for(int i = 0; i < n; i++) cin >> original[i].X >> original[i].Y;
  for(int i = 0; i < n; i++) calc(i);
//  calc(0);
  cout << tot;


}
