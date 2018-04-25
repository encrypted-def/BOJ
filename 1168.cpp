#include <stdio.h>
#include <assert.h>
int BIT[100010];
int N, M;
int sum(int i) {
	int ret = 0;
	while (i > 0) {
		ret += BIT[i];
		i -= (i & -i);
	}
	return ret;
}
void update(int i, int num) {
	while (i <= N) {
		BIT[i] += num;
		i += (i & -i);
	}
}
int count_person(int i, int j) {
	j = j % N;
	if (j == 0) j = N;
	if (j >= i)
		return sum(j) - sum(i);
	return sum(N) - sum(i) + sum(j);
}
int main(void) {
	scanf("%d %d", &N, &M);
	for(int i = 1; i <= N; i++)
		update(i, 1);
	printf("<%d", M);
	update(M, -1);
	int cur = M;
	int left = N-1;
	while (left > 0) {
		// count_person(cur, i) = N인 최소의 i를 찾고싶다.
		int st = cur + 1;
		int en = cur + N;
		while (st < en) {			
			int mid = (st + en) / 2;
			int val = count_person(cur, mid);			
			int M_mod = M % left;
			if (M_mod == 0) M_mod = left;
			if (val < M_mod)
				st = mid + 1;
			else if (val == M_mod)
				en = mid;
			else
				en = mid - 1;
			
		}	
		assert(st == en);
		st = st % N;
		if (st == 0) st = N;
		printf(", %d", st);
		cur = st;
		update(st, -1);
		left--;
	}
	printf(">");
}
