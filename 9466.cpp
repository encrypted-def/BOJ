#include <bits/stdc++.h>
using namespace std;

int arr[100005];
int n;
int state[100005];

const int NOT_VISITED = 0;
const int VISITED = 1;
const int CYCLE_IN = 2;
const int NOT_CYCLE_IN = 3;

void run(int x){
  int cur = x;
  while(true){
    state[cur] = VISITED;
    cur = arr[cur];
    // 1번 케이스
    if(state[cur] == CYCLE_IN || state[cur] == NOT_CYCLE_IN){
      cur = x;
      while(state[cur] == VISITED){
        state[cur] = NOT_CYCLE_IN;
        cur = arr[cur];
      }
      return;
    }
    // 2번 케이스
    if(state[cur] == VISITED && cur != x){
      while(state[cur] != CYCLE_IN){
        state[cur] = CYCLE_IN;
        cur = arr[cur];
      }
      cur = x;
      while(state[cur] != CYCLE_IN){
        state[cur] = NOT_CYCLE_IN;
        cur = arr[cur];
      }
      return;
    }
    // 3번 케이스
    if(state[cur] == VISITED && cur == x){
      while(state[cur] != CYCLE_IN){
        state[cur] = CYCLE_IN;
        cur = arr[cur];
      }
      return;
    }
  }
}

int main(void){
  ios::sync_with_stdio(0);
  cin.tie(0);
  int t;
  cin >> t;
  while(t--){
    cin >> n;
    fill(state+1, state+n+1, 0);
    for(int i = 1; i <= n; i++)
      cin >> arr[i];
    int ans = 0;
    for(int i = 1; i <= n; i++){
      if(state[i] == NOT_VISITED) run(i);
    }
    int cnt = 0;
    for(int i = 1; i <= n; i++){
      if(state[i] == NOT_CYCLE_IN) cnt++;
    }
    cout << cnt << '\n';
  }
}
