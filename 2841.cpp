#include <vector>
#include <stdio.h>
using namespace std;
int main(void) {
	int N, P;
	scanf("%d %d", &N, &P);
	vector<int> string[6]; // increasing order로 누르고있는 flat의 정보가 저장되어있음
	int cnt = 0;
	while (N--) {
		int a, b;
		scanf("%d %d", &a, &b);
		while (!string[a - 1].empty() && string[a - 1].back() > b) {
			string[a - 1].pop_back(); // 손을 뗌
			cnt++;
		}
		if (!string[a - 1].empty() && string[a - 1].back() == b)
			continue;
		string[a - 1].push_back(b); // 손을 붙임
		cnt++;
	}
	printf("%d", cnt);
}
