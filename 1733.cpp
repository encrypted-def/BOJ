#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef tuple<int, int, int> ti3;
typedef tuple<int, int, int, int> ti4;
typedef stack<int> si;
typedef queue<int> qi;
typedef priority_queue<int> pqi;
typedef pair<ll, ll> pll;
typedef vector<ll> vl;
typedef tuple<ll, ll, ll> tl3;
typedef tuple<ll, ll, ll, ll> tl4;
typedef stack<ll> sl;
typedef queue<ll> ql;
typedef priority_queue<ll> pql;
int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };
int ddx[8] = { 0,0,1,1,1,-1,-1,-1 }, ddy[8] = { 1,-1,1,0,-1,1,0,-1 };
ll MOD = 1000000000;
ll POW(ll a, ll b, ll MMM = MOD) { ll ret = 1; for (; b; b >>= 1, a = (a*a) % MMM)if (b & 1)ret = (ret*a) % MMM; return ret; }
ll GCD(ll a, ll b) { return b ? GCD(b, a%b) : a; }
ll LCM(ll a, ll b) { if (a == 0 || b == 0)return a + b; return a * (b / GCD(a, b)); }
ll INV(ll a, ll m) {
  ll m0 = m, y = 0, x = 1;
  if (m == 1)	return 0;
  while (a > 1) {
    ll q = a / m;
    ll t = m;
    m = a % m, a = t;
    t = y;
    y = x - q * y;
    x = t;
  }
  if (x < 0) x += m0;
  return x;
}
ll EXGCD(ll a, ll b, ll&x, ll&y) {
  if (!b)return x = 1, y = 0, a;
  ll d = EXGCD(b, a%b, x, y), t = x;
  return x = y, y = t - a / b * y, d;
}
bool OOB(ll x, ll y, ll N, ll M) { return 0 > x || x >= N || 0 > y || y >= M; }
#define X first
#define Y second
#define rep(i,a,b) for(int i = a; i < b; i++)
#define pb(x) push_back(x)
#define all(x) (x).begin(), (x).end()
#define sf1(a) cin >> a
#define sf2(a,b) cin >> a >> b
#define sf3(a,b,c) cin >> a >> b >> c
#define sf4(a,b,c,d) cin >> a >> b >> c >> d
#define sf5(a,b,c,d,e) cin >> a >> b >> c >> d >> e
#define sf6(a,b,c,d,e,f) cin >> a >> b >> c >> d >> e >> f
#define pf1(a) cout << (a) << ' '
#define pf2(a,b) cout << (a) << ' ' << (b) << ' '
#define pf3(a,b,c) cout << (a) << ' ' << (b) << ' '<< (c) << ' '
#define pf4(a,b,c,d) cout << (a) << ' ' << (b) << ' '<< (c) << ' '<< (d) << ' '
#define pf5(a,b,c,d,e) cout << (a) << ' ' << (b) << ' '<< (c) << ' '<< (d) << ' '<< (e) << ' '
#define pf6(a,b,c,d,e,f) cout << (a) << ' ' << (b) << ' '<< (c) << ' '<< (d) << ' '<< (e) << ' ' << (f) << ' '
#define pf0l() cout << '\n';
#define pf1l(a) cout << (a) << '\n'
#define pf2l(a,b) cout << (a) << ' ' << (b) << '\n'
#define pf3l(a,b,c) cout << (a) << ' ' << (b) << ' '<< (c) << '\n'
#define pf4l(a,b,c,d) cout << (a) << ' ' << (b) << ' '<< (c) << ' '<< (d) << '\n'
#define pf5l(a,b,c,d,e) cout << (a) << ' ' << (b) << ' '<< (c) << ' '<< (d) << ' '<< (e) << '\n'
#define pf6l(a,b,c,d,e,f) cout << (a) << ' ' << (b) << ' '<< (c) << ' '<< (d) << ' '<< (e) << ' ' << (f) << '\n'

int n;
vi occur[1000005];
pii shirt[1000005];

int choice[1000005];
int isused[1000005];

vector<pii> adj[1000005];
pii p[1000005];
int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  sf1(n);
  qi fixed;
  rep(i,0,n){
    int a,b;
    sf2(a,b);
    if(a == b){
      if(isused[a]){
        pf1l(-1);
        return 0;
      }
      fixed.push(a);
      isused[a] = 1;
      choice[i] = a;
      shirt[i] = {a, a};
    }
    else{
      occur[a].pb(i);
      occur[b].pb(i);
      shirt[i] = {a,b};
    }
  }
  while(!fixed.empty()){
    int cur = fixed.front(); fixed.pop();
    for(auto v : occur[cur]){
      if(choice[v] != 0) continue;
      int other = shirt[v].X + shirt[v].Y - cur;
      if(isused[other]){
        pf1l(-1);
        return 0;
      }
      isused[other] = 1;
      choice[v] = other;
      fixed.push(other);
    }
  }
  rep(i,0,n){
    if(choice[i] != 0) continue;
    int a, b;
    tie(a,b) = shirt[i];
    adj[a].pb(make_pair(b, i));
    adj[b].pb(make_pair(a, i));    
  }
  rep(i,1,1000001){
    if(isused[i]) continue;
    int left = -1; // tree에 속하지 않는 간선의 index
    queue<int> q;
    q.push(i);
    isused[i] = 1;
    while(!q.empty()){
      int cur = q.front(); q.pop();
      for(auto nxt : adj[cur]){  
        if(isused[nxt.X]){
          if(nxt.X == p[cur].X || left == nxt.Y) continue;
          else{
            if(left != -1){
              pf1l(-1);
//              assert(0);
              return 0;
            }
            left = nxt.Y;
            continue;
          }
        }
        p[nxt.X] = {cur, nxt.Y};
        choice[nxt.Y] = nxt.X;
        q.push(nxt.X);
        isused[nxt.X] = 1;
      }
    }
    if(left != -1){
      int a, b;
      tie(a, b) = shirt[left];
      choice[left] = a;
      while(a != i){
        choice[p[a].Y] = p[a].X;
        a = p[a].X;
      }
    }
  }
  rep(i,0,n){
    pf1l(choice[i]);
    assert(choice[i] == shirt[i].X or choice[i] == shirt[i].Y);
  }
}
