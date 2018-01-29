#include <stdio.h>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
int N;
int S[22][22];
int main(void) {
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			scanf("%d", &S[i][j]);
	vector<int> team(N, -1);
	fill(team.begin() + N / 2, team.end(), 1);
	int mn = 0x7ffffff;
	do {
		int cnt = 0;
		for (int i = 1; i <= N; i++) {
			for (int j = i+1; j <= N; j++) {
				if (team[i-1] == team[j-1])
					cnt += team[i-1] * (S[i][j] + S[j][i]);
			}
		}
		mn = min(mn, abs(cnt));
	} while (next_permutation(team.begin(), team.end()));
	printf("%d", mn);
}
