#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define X first
#define Y second
#define pb push_back

int l,k;
ll D[103];

int main(void){
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> l >> k;
  D[1] = D[k] = 1;
  for(int i = 2; i <= l; i++){
    D[i] += D[i-2];
    if(i >= k+1) D[i] += D[i-k-1];
  }
  ll tot = 0;
  for(int i = 1; i <= l; i++) tot += D[i];
  cout << tot;

}
