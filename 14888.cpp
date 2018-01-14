#include <stdio.h>
#include <algorithm>
#include <vector>
using namespace std;
int main(void) {
	int N;
	int A[13];
	int op[4]; // + - * /
	scanf("%d", &N);
	for(int i = 0; i < N; i++)
		scanf("%d", &A[i]);
	scanf("%d %d %d %d", &op[0], &op[1], &op[2], &op[3]);
	vector<int> op_brute;
	for (int i = 0; i < 4; i++)
		while(op[i]--)
			op_brute.push_back(i);
	int mn = 0x7fffffff;
	int mx = 0x80000000;
	do {
		int mid = A[0];
		for (int i = 0; i < N - 1; i++) {
			if (op_brute[i] == 0)
				mid += A[i + 1];
			if (op_brute[i] == 1)
				mid -= A[i + 1];
			if (op_brute[i] == 2)
				mid *= A[i + 1];
			if (op_brute[i] == 3)
				mid /= A[i + 1];
		}
		mx = max(mx, mid);
		mn = min(mn, mid);
	} while (next_permutation(op_brute.begin(), op_brute.end()));
	printf("%d\n%d", mx, mn);
}
