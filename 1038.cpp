#include <stdio.h>
#include <algorithm>
#include <vector>
using namespace std;
int main(void) {
	vector<long long> dec_num;
	for (int i = 1; i <= 1023; i++) { // {0, 1, 2, 3, .. , 9}의 공집합이 아닌 부분집합을 뽑아내기 위해서.
		long long num = 0; // i에 대응되는 감소하는 수
		int tmp_i = i;
		for (int idx = 9; idx >= 0; idx--) {
			if (tmp_i % 2 == 1)
				num = 10 * num + idx; // idx를 1의 자리에 넣음
			tmp_i /= 2;
		}
		dec_num.push_back(num); // i에 대응되는 감소하는 수를 list에 넣음
	}
	sort(dec_num.begin(), dec_num.end());
	int N;
	scanf("%d", &N);
	if (N > 1022)
		printf("-1");
	else
		printf("%lld", dec_num[N]);
	return 0;
}
