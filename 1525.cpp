#include <bits/stdc++.h>

using namespace std;

vector<char> i2vc(int i) {
  vector<char> ret(9);
  int k = 9;
  while (k--) {
    ret[k] = i % 10;
    i /= 10;
  }
  return ret;
}
int vc2i(vector<char> vc) {
  int ret = 0;
  for (int i = 0; i < 9; i++) {
    ret = 10 * ret + vc[i];
  }
  return ret;
}
bool isDone(vector<char> vc) {
  for (int i = 0; i < 9; i++) {
    if (vc[i] != i + 1) return 0;
  }
  return 1;
}
int main(void) {
  // ios::sync_with_stdio(false);
  // cin.tie(0);
  int ssz = 0;
  vector<char> init(9);
  set<int> isVisited;
  for (int i = 0; i < 9; i++) {
    cin >> init[i];
    init[i] -= '0';
    if (init[i] == 0) {
      init[i] = 9;
    }
  }
  if (isDone(init)) {
    cout << 0;
    return 0;
  }
  queue<pair<int, char> > Q;
  Q.push({vc2i(init), 0});
  isVisited.insert(vc2i(init));
  while (!Q.empty()) {
    pair<int, char> ttt = Q.front();
    int cur = ttt.first;
    int depth = ttt.second;
    Q.pop();
    int pos9 = -1;
    vector<char> curBoard = i2vc(cur);
    for (int i = 0; i < 9; i++) {
      if (curBoard[i] == 9) {
        pos9 = i;
        break;
      }
    }
    assert(pos9 != -1);
    int dd[4] = {-3, -1, 1, 3};
    for (int dir = 0; dir < 4; dir++) {
      if (0 <= pos9 + dd[dir] and pos9 + dd[dir] <= 8) {
        if (pos9 % 3 == 0 and dd[dir] == -1) continue;
        if (pos9 % 3 == 2 and dd[dir] == 1) continue;
        swap(curBoard[pos9], curBoard[pos9 + dd[dir]]);
        if (isVisited.find(vc2i(curBoard)) != isVisited.end()) {
          swap(curBoard[pos9], curBoard[pos9 + dd[dir]]);
          continue;
        }
        int nxt = vc2i(curBoard);
        Q.push({nxt, depth + 1});
        isVisited.insert(nxt);
        if (isDone(curBoard)) {
          cout << (int)depth + 1;
          return 0;
        }
        swap(curBoard[pos9], curBoard[pos9 + dd[dir]]);
      }
    }
  }
  assert(false);
  cout << -1;
}
