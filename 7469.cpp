#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
typedef pair<int, int> PAIR;
#define X first
#define Y second
int arr[100005];
vector<int> segment[300005];
int n, m;
PAIR tmp[100005]; // 7 3 5가 입력이라면 (3, 2), (5, 3), (7, 1)을 가지고 있음
int number_place[100005]; // 7 3 5가 입력이라면 numbering을 끝낸 후에 3 1 2 순으로 있는 거니 number_place[1] = 2, number_place[2] = 3이다.
int recoverNum[100005]; // 7 3 5가 입력이라면 3 5 7을 저장하고 있음
void update(int i, int val, int node, int node_st, int node_en) {
	if (node_st > i || i > node_en) // 범위 밖인경우
		return;
	if (node_st == node_en) { // leaf에 도달한 경우
		segment[node].push_back(val);
		return;
	}
	segment[node].push_back(val);
	int mid = (node_st + node_en) / 2;
	update(i, val, node * 2, node_st, mid);
	update(i, val, node * 2+1, mid+1, node_en);
}

int query(int a, int b, int val, int node, int node_st, int node_en) { // val이 a~b에서 몇번째인지 구해주는 함수
	if (node_en < a || b < node_st) // a~b와 node_st~node_en 범위가 아예 겹치지 않는 경우
		return 0;
	if (a <= node_st && node_en <= b) // node_st~node_en 범위가 a~b 범위 안에 완벽하게 들어가는 경우
		return lower_bound(segment[node].begin(), segment[node].end(), val) - segment[node].begin() ;
	int mid = (node_st + node_en) / 2;
	return query(a, b, val, node * 2, node_st, mid) + query(a, b, val, node * 2 + 1, mid + 1, node_en);
}

int main(void) {
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		scanf("%d", &tmp[i].X);
		tmp[i].Y = i+1;
	}
	sort(tmp, tmp + n);
	for (int i = 0; i < n; i++) {
		update(tmp[i].second, i+1, 1, 1, n);
		number_place[i+1] = tmp[i].second;
		recoverNum[i+1] = tmp[i].first;
	}
	for (int i = 1; !segment[i].empty(); i++) { // 빈 segment에 도달할 때 까지
		sort(segment[i].begin(), segment[i].end());
	}
	while (m--) {
		int i, j, k;
		scanf("%d %d %d", &i, &j, &k);
		int lo = 1;
		int hi = n;
		int mid = (lo+hi)/2;		
		while (true) {
			int calc = query(i, j, mid, 1, 1, n)+1;
			if (calc < k) // mid의 순위가 더 낮음. mid를 더 크게 해야함
				lo = mid+1;
			else if (calc == k) { // mid가 k번쨰에 삽입될 수 있음
				if (i <= number_place[mid] && number_place[mid] <= j) { // a~b 범위안에 mid가 존재하는 경우
					printf("%d\n", recoverNum[mid]);
					break;
				} // a~b 범위 안에 mid가 존재하지 않는 경우
				else
					lo = mid+1; // mid를 더 크게 해야함
			}
			else
				hi = mid-1;
			mid = (lo + hi) / 2;
		}
	}
}
