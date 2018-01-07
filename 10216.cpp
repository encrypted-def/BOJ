#include <stdio.h>
#include <algorithm>
#include <stack>
using namespace std;
typedef pair<int, int> PAIR;
#define X first
#define Y second
int N;
PAIR coor[3003];
int R[3003];
bool isVisited[3003];
int square(int a) {
	return a*a;
}
int dist(int i, int j) {
	return square(coor[i].X - coor[j].X) + square(coor[i].Y - coor[j].Y);
}
int main(void) {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &N);
		fill(isVisited, isVisited + N, false);
		for (int i = 0; i < N; i++) 
			scanf("%d %d %d", &coor[i].X, &coor[i].Y, &R[i]);
		int cnt = 0;
		stack<int> S;
		for (int i = 0; i < N; i++) {
			if (isVisited[i])
				continue;
			S.push(i);
			isVisited[i] = true;
			cnt++;
			while (!S.empty()) {
				int cur = S.top();
				S.pop();
				for (int cand = 0; cand < N; cand++) {
					if (!isVisited[cand] && dist(cur, cand) <= square(R[cur] + R[cand])) {
						isVisited[cand] = true;
						S.push(cand);
					}
				}

			}
		}
		printf("%d\n", cnt);
	}
}
