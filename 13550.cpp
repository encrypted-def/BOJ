#include<bits/stdc++.h>
using namespace std;
#define X first
#define Y second
#define pb push_back
typedef long long ll;
typedef tuple<int,int,int> ti3;
int sz = 2000;
int n,k;
int a[100004];
int b[100004]; // b[i] = a[1]+..+a[i]
list<int> r[1000004];
int cnt[1000004];
int bucket[1001];
bool cmp(ti3 a, ti3 b){
  if(get<0>(a) / sz != get<0>(b) / sz) return get<0>(a) / sz < get<0>(b) / sz;
  return get<0>(a) / sz % 2 ? get<1>(a) > get<1>(b) : get<1>(a) < get<1>(b);
}
int list_sz(int x){
  return r[x].back()-r[x].front();
}
void mo_add(int x){
  if(r[b[x]].size() >= 2){
    cnt[list_sz(b[x])]--;
    bucket[list_sz(b[x])/sz]--;
  }
  if(r[b[x]].empty() or r[b[x]].front() > x) r[b[x]].push_front(x);
  else r[b[x]].push_back(x);
  if(r[b[x]].size() >= 2){
    cnt[list_sz(b[x])]++;
    bucket[list_sz(b[x])/sz]++;
  }
}
void mo_erase(int x){
  if(r[b[x]].size() >= 2){
    cnt[list_sz(b[x])]--;
    bucket[list_sz(b[x])/sz]--;
  }

  if(r[b[x]].front() == x) r[b[x]].pop_front();
  else r[b[x]].pop_back();

  if(r[b[x]].size() >= 2){
    cnt[list_sz(b[x])]++;
    bucket[list_sz(b[x])/sz]++;
  }

}
int main(void){
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> n >> k;
  for(int i = 1; i <= n; i++){
    cin >> a[i];
    a[i] %= k;
    b[i] = (b[i-1]+a[i]) % k;
  }
  int m;
  cin >> m;
  ti3 query[m];
  int ans[m];
  for(int i = 0; i < m; i++){
    int l,r;
    cin>>l>>r;
    query[i] = {l-1,r,i};
  }
  sort(query,query+m, cmp);
  int st = 0;
  int en = 0;
  mo_add(0);
  cnt[0] = bucket[0] = 2*k;
  for(int i = 0; i < m; i++){
    int l,r,idx;
    tie(l,r,idx) = query[i];
    while(st > l) mo_add(--st);
    while(en < r) mo_add(++en);
    while(st < l) mo_erase(st++);
    while(en > r) mo_erase(en--);
    int j = (n+1)/sz;
    while(bucket[j]==0) j--;
    int val = min((j+1)*sz,n);
    while(cnt[val]==0) val--;
    ans[idx] = val;
  }
  for(int i = 0; i < m; i++) cout << ans[i] << '\n';
}#include<bits/stdc++.h>
using namespace std;
#define X first
#define Y second
#define pb push_back
typedef long long ll;
typedef tuple<int,int,int> ti3;
int sz = 2000;
int n,k;
int a[100004];
int b[100004]; // b[i] = a[1]+..+a[i]
list<int> r[1000004];
int cnt[1000004];
int bucket[1001];
bool cmp(ti3 a, ti3 b){
  if(get<0>(a) / sz != get<0>(b) / sz) return get<0>(a) / sz < get<0>(b) / sz;
  return get<0>(a) / sz % 2 ? get<1>(a) > get<1>(b) : get<1>(a) < get<1>(b);
}
int list_sz(int x){
  return r[x].back()-r[x].front();
}
void mo_add(int x){
  if(r[b[x]].size() >= 2){
    cnt[list_sz(b[x])]--;
    bucket[list_sz(b[x])/sz]--;
  }
  if(r[b[x]].empty() or r[b[x]].front() > x) r[b[x]].push_front(x);
  else r[b[x]].push_back(x);
  if(r[b[x]].size() >= 2){
    cnt[list_sz(b[x])]++;
    bucket[list_sz(b[x])/sz]++;
  }
}
void mo_erase(int x){
  if(r[b[x]].size() >= 2){
    cnt[list_sz(b[x])]--;
    bucket[list_sz(b[x])/sz]--;
  }

  if(r[b[x]].front() == x) r[b[x]].pop_front();
  else r[b[x]].pop_back();

  if(r[b[x]].size() >= 2){
    cnt[list_sz(b[x])]++;
    bucket[list_sz(b[x])/sz]++;
  }

}
int main(void){
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> n >> k;
  for(int i = 1; i <= n; i++){
    cin >> a[i];
    a[i] %= k;
    b[i] = (b[i-1]+a[i]) % k;
  }
  int m;
  cin >> m;
  ti3 query[m];
  int ans[m];
  for(int i = 0; i < m; i++){
    int l,r;
    cin>>l>>r;
    query[i] = {l-1,r,i};
  }
  sort(query,query+m, cmp);
  int st = 0;
  int en = 0;
  mo_add(0);
  cnt[0] = bucket[0] = 2*k;
  for(int i = 0; i < m; i++){
    int l,r,idx;
    tie(l,r,idx) = query[i];
    while(st > l) mo_add(--st);
    while(en < r) mo_add(++en);
    while(st < l) mo_erase(st++);
    while(en > r) mo_erase(en--);
    int j = (n+1)/sz;
    while(bucket[j]==0) j--;
    int val = min((j+1)*sz,n);
    while(cnt[val]==0) val--;
    ans[idx] = val;
  }
  for(int i = 0; i < m; i++) cout << ans[i] << '\n';
}
