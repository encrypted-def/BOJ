#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
#define X first
#define Y second
int N,E;

///////// 1-indexed ///////////
vector<int> adj[100005];
vector<int> child[100005];
vector<int> parent, st, en, low, depth;
int Time = 1;
int dfs(int cur){
  st[cur] = low[cur] = Time++;
  for(auto n : adj[cur]){
    if(depth[n]!=-1){
      if(parent[cur]!=n) low[cur] = min(low[cur],st[n]);
      continue;
    }
    depth[n] = depth[cur]+1;
    parent[n] = cur;
    child[cur].push_back(n);
    dfs(n);
    low[cur] = min(low[cur],low[n]);
  }
  en[cur] = Time++;
}
// tree상에서 a가 b의 자식인가?
bool isDesc(int a, int b){
  return st[b] <= st[a] && en[a] <= en[b];
}

// anc의 자식 노드 중에 desc를 자손으로 가지고 있는 것을 반환
int getSubtree(int anc, int desc){
  int lo=0,hi = child[anc].size()-1;
  while(lo != hi){
    int mid=(lo + hi)/2;
    if(st[desc] > en[child[anc][mid]]) lo = mid + 1;
    else if(en[desc] < st[child[anc][mid]]) hi = mid - 1;
    else return child[anc][mid];
  }
  return child[anc][lo];
}
void traveling(){
  parent.resize(N+1), st.resize(N+1), en.resize(N+1), low.resize(N+1),depth.resize(N+1,-1);
  parent[1] = -1;
  depth[1] = 1;
  dfs(1);
}
int main(void){
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> N >> E;
  while(E--){
    int a,b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  traveling();
  int Q;
  cin >> Q;
  while(Q--){
    int comm;
    cin >> comm;
    if(comm == 1){
      int A,B,G1,G2;
      cin>>A>>B>>G1>>G2;
      if(isDesc(G1,G2)) swap(G1,G2);
      if(depth[G2] != depth[G1]+1) cout << "yes\n"; // tree에 속하지 않는 edge라면

      else if(low[G2] < st[G2]) cout << "yes\n"; // 절단선이 아니라면
      else if(isDesc(A,G2)==isDesc(B,G2)) cout << "yes\n"; // A,B가 같은 영역에 있다면
      else cout << "no\n";
    }
    else{
      int A,B,C;
      cin>>A>>B>>C;
      if(!isDesc(A,C)&& !isDesc(B,C)) cout << "yes\n"; // A, B 모두 C의 자손이 아니라면
      else if(isDesc(A,C) && isDesc(B,C)){ // A, B 둘다 C의 자손이라면
        int c1 = getSubtree(C,A);
        int c2 = getSubtree(C,B);
        if(c1==c2) cout << "yes\n"; // LCA가 C 밑에 있으니 당연
        else if(low[c1] < st[C] && low[c2] < st[C]) cout << "yes\n"; // dfs 특성상 c1 c2 사이에 다른 선이 있을 수는 없음. 그러니 둘 다 low가 C를 넘겨야 함
        else cout << "no\n";
      }
      else{ // B는 C의 자손이고 A는 C의 자손이 아닐 때
        if(isDesc(A,C)) swap(A,B);
        int c1 = getSubtree(C,B);
        if(low[c1] < st[C]) cout <<"yes\n"; // B에서 C 위로 갈 수 있는 우회로가 있으면
        else cout << "no\n";
      }
    }
  }
}
