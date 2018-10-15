#include<bits/stdc++.h>
using namespace std;
#define X first
#define Y second
#define pb push_back
typedef long long ll;


// 1. 각 pattern에 대해 insert 함수 실행
// 2. Aho 함수 실행(Fail 함수는 Aho함수가 call함)
// 3. 현재 코드는 패턴의 등장 횟수를 계산하는 코드. 상황에 맞게 Aho, c2i 함수 수정
class Node {
public:
	int pt, fail;
	vector<int> next;
	Node(int num):next(num) {
		pt = 0;
		fail = 0;
	}
};

class Trie {
public:
  int nsz;  // node size
  vector<Node> node;
  int mx; // max node num
  int num;  // kind of character(ex : a to z -> 26, 0 to 9 -> 10)
  Trie(int mx, int num) : mx(mx), num(num) {
    node.resize(mx, Node(num));
    nsz = 1;
  }
  int c2i(char c) {  // character to int, 0 to num-1
    return c-'A';
  }
  void insert(string& p, int strcost)  // ptag : pattern의 tag
  {
    int cur = 0;
    for (auto& c : p) {
      int n = c2i(c);
      if (node[cur].next[n] == 0) {
        node[cur].next[n] = nsz;
        cur = nsz++;
      }
      else cur = node[cur].next[n];
    }
    node[cur].pt = strcost;    
  }

  void Fail() { // 0 : root
    queue<int> q;
    node[0].fail = 0;
    q.push(0);
    while (!q.empty()) {
      int cur = q.front();
      q.pop();
      for (int n = 0; n < num; ++n) {
        int child = node[cur].next[n];
        if (!child) continue;
        if (cur == 0)
          node[child].fail = 0;
        else {
          int t = node[cur].fail;
          while (t != 0 && node[t].next[n] == 0) t = node[t].fail;
          if (node[t].next[n]) t = node[t].next[n];
          node[child].fail = t;
        }
        if (node[node[child].fail].pt != 0)
          node[child].pt += node[node[child].fail].pt;
        q.push(child);
      }
    }
  }
  int findnxt(int cur, int n){
    while(cur and node[cur].next[n] == 0) cur = node[cur].fail;
    return node[cur].next[n];    
  }

  int Aho(string& s) {
    Fail();
    int cnt = 0;
    int cur = 0;
    for (int i = 0; i < s.size(); i++) {
      int n = c2i(s[i]);
      while (cur and node[cur].next[n] == 0) cur = node[cur].fail;
      if (node[cur].next[n]) cur = node[cur].next[n];
      if (node[cur].pt != -1) cnt += node[cur].pt;
    }
    return cnt;
  }
};

int main(void){
  ios::sync_with_stdio(0);
  cin.tie(0);
  int T;
  cin >> T;
  for(int Case = 1; Case <= T; Case++){
    int N,M,B;
    cin >> N >> M >> B;
    int cost[26];
    Trie TR(10000,26);
    fill(cost,cost+26,-1);
    for(int i = 0; i < N; i++){
      string s;
      int c;
      cin >> s >> c;
      cost[s[0]-'A'] = c;
    }
    for(int i = 0; i < M; i++){
      string s;
      int c;
      cin >> s >> c;
      TR.insert(s,c);
    }
    TR.Fail();
    int D[10000][201] = {};
    memset(D,0xff,sizeof(D));
    int mx = 0;
    D[0][0]=0;
    for(int i = 0; i <= B; i++){
      for(int j = 0; j < TR.nsz; j++){
        if(D[j][i]==-1) continue;
        mx = max(mx,D[j][i]);
//        printf("D[%d][%d] : %d\n",j,i,D[j][i]);
        for(int n = 0; n < 26; n++){
          if(cost[n] == -1 or i+cost[n] > B) continue;
          int nxt = TR.findnxt(j,n);
          if(nxt == 0) continue;
//          printf("n : %d\n",n);
          D[nxt][i+cost[n]] = max(D[nxt][i+cost[n]],D[j][i]+TR.node[nxt].pt);
        }
      }
    }
    cout << "Case #" << Case << ": " << mx << '\n';


  }
}
