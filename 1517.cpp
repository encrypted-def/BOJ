#include <stdio.h>
#include <vector>
using namespace std;
int N;
int A[500003];
long long cnt = 0;
void swap(int* a, int* b) {
	int c = *a;
	*a = *b;
	*b = c;
}
void merge(int st, int mid, int en) {
	vector<int> V;
	int i = 0, j = 0, len1 = mid - st, len2 = en - mid;
	while (i < len1 && j < len2) {
		if (A[st+i] > A[mid+j]) {
			cnt += len1 - i;
			V.push_back(A[mid+j++]);
		}
		else
			V.push_back(A[st+i++]);
	}
	while (i < len1)
		V.push_back(A[st+i++]);
	while (j < len2)
		V.push_back(A[mid+j++]);
	for (int i = st; i < en; i++)
		A[i] = V[i - st];
}
void mergesort(int st, int en) {
	if (en == st+1) return;
	if (en == st + 2) {
		if (A[st] > A[st+1]) {
			cnt++;
			swap(&A[st], &A[st + 1]);
		}
		return;
	}
	int mid = (st + en) / 2;
	mergesort(st, mid);
	mergesort(mid, en);
	merge(st, mid, en);
}
int main(void) {
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%d", &A[i]);
	mergesort(0, N);
	printf("%lld", cnt);
}
