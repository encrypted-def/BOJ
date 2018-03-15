#include <stdio.h>
#include <algorithm>
using namespace std;
int N, d, k, c;
int arr[30005];
int kind[3005];
int main(void) {
	scanf("%d %d %d %d", &N, &d, &k, &c);
	for (int i = 0; i < N; i++)
		scanf("%d", &arr[i]);
	int tot = 0;
	for (int i = N - k; i < N; i++) {
		if (kind[arr[i]] == 0)
			tot++;
		kind[arr[i]]++;
	}
	int mx = 0;
	for (int i = 0; i < N; i++) {
		if (kind[arr[i]] == 0)
			tot++;
		kind[arr[i]]++;
		int del_dish = i - k;
		if (del_dish < 0)
			del_dish += N;
		if (kind[arr[del_dish]] == 1)
			tot--;
		kind[arr[del_dish]]--;
		mx = max(mx, tot + (kind[c] == 0));
	}
	printf("%d", mx);
}
