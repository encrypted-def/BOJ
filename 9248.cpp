/*

banana -> 4번째
anana -> 3번째
nana -> 6번째
ana -> 2번째
na -> 5번째
a -> 1번째
x -> 4 3 6 2 5 1

a 6
ana 4
anana 2
banana 1
na 5
nana 3

*/

#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <functional>
#include <tuple>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef tuple<int, int, int> ti3;
int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };
#define X first
#define Y second
const int MX = 500003;
char S[MX] = "abracadabra";
int N;
int sa[MX], pos[MX], lcp[MX];
ti3 node[MX], tmp[MX]; // 앞 d글자의 value / 뒤 d글자의 value / index

void SuffixArray() {
	
	for (int i = 0; i < N; i++) {
		get<0>(node[i]) = S[i] - 'a';
		get<1>(node[i]) = i != N - 1 ? S[i + 1] - 'a' : -1;
		get<2>(node[i]) = i;
	}
	sort(node, node + N);
	for (int d = 2; d < N; d <<= 1) {
		int M = 0, val = get<0>(node[0]);
		get<0>(node[0]) = pos[get<2>(node[0])] = 0;
		for (int i = 1; i < N; i++) {
			if (val == get<0>(node[i]) && get<1>(node[i - 1]) == get<1>(node[i]))
				get<0>(node[i]) = M;
			else {
				val = get<0>(node[i]);
				get<0>(node[i]) = ++M;
			}
			pos[get<2>(node[i])] = i;
		}
		M++;	
		vi cnt(MX + 1, 0);
		for (int i = 0; i < N; i++) {
			int j = get<2>(node[i]) + d;
			get<1>(node[i]) = (j < N ? get<0>(node[pos[j]]) : -1);
			cnt[get<1>(node[i]) + 1]++; // -1 때문에
		}
		for (int i = 1; i < M + 1; i++) cnt[i] += cnt[i - 1];
		for (int i = N - 1; i >= 0; i--)
			tmp[--cnt[get<1>(node[i]) + 1]] = node[i];
		// 뒤 d글자의 value로 정렬 완료
		fill(cnt.begin(), cnt.end(), 0);
		for (int i = 0; i < N; i++) cnt[get<0>(tmp[i])]++;
		for (int i = 1; i < M; i++) cnt[i] += cnt[i - 1];
		for (int i = N - 1; i >= 0; i--)
			node[--cnt[get<0>(tmp[i])]] = tmp[i];
	}
	for (int i = 0; i < N; i++) {
		sa[i] = get<2>(node[i]);
		pos[sa[i]] = i;
	}
}
void LCP() {
	for (int i = 0, k = 0; i < N; i++, k = max(k - 1, 0)) {
		if (pos[i] == N - 1) continue;
		for (int j = sa[pos[i] + 1]; S[i + k] == S[j + k]; k++);
		lcp[pos[i]] = k;
	}
}

int main() {
	scanf("%s", S);
	N = strlen(S);
	SuffixArray();
	LCP();
	for (int i = 0; i<N; i++)
		printf("%d ", sa[i] + 1);
	printf("\nx ");
	for (int i = 0; i<N - 1; i++)
		printf("%d ", lcp[i]);
}

