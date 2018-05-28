
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
int N;
int A, B;
ll YY[2005];
ll sum[2003][2003];
int D[2003] = { 0, };
bool solve1(ll target) { // target에 있는 bit만 등장하는 것이 가능한가?
	
	if ((YY[0] | target) == target) D[1] = 1;
	else D[1] = 0x7f7f7f7f;
	for (int i = 2; i < N + 1; i++) {
		D[i] = 0x7f7f7f7f;
		for (int j = 0; j < i; j++) {
			if (D[j] == 0x7f7f7f7f) continue;
			if (((sum[j][i] | target) == target) && (D[i] > D[j] + 1))
				D[i] = D[j] + 1;
		}
	}	
	return D[N] <= B;
}
void A1() { // N > 100일 때(A = 1임이 보장)
	ll target = (1ll << 41)-1;
	for (int i = 40; i >= 0; i--) {
		target -= (1ll << i);
		if (!solve1(target))
			target += (1ll << i);
	}
	cout << (target);
}

bool solve2(ll target) {
	bool D[104][104] = { 0, }; // D[N][k] : N개의 조각상을 k개의 그룹으로 쪼갤 때 target bit로만 구성되어있는가?
	D[0][0] = true;
	for (int i = 1; i < N + 1; i++) {
		for (int k = 1; k < min(i, B) + 1; k++) {
			for(int sep = 0; sep < i; sep++) {
				if (D[sep][k-1] && ((sum[sep][i] | target) == target)) {
					D[i][k] = true;
					if (i == N && k >= A) return true;
				}
			}
		}
	}
	return false;
}
void A2() { // N <= 100일 때
	ll target = (1ll << 45)-1;
	for (int i = 44; i >= 0; i--) {
		target = target -= (1ll << i);
		if (!solve2(target))
			target += (1ll << i);
	}
	cout << (target);
}
int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> N >> A >> B;
	for (int i = 0; i < N; i++) {
		cin >> YY[i];
		sum[i][i + 1] = YY[i];
	}
	for (int i = 0; i < N; i++)
		for (int j = i+2; j < N + 1; j++) sum[i][j] = sum[i][j - 1] + YY[j - 1];
	if (A != 1) A2();
	else A1();
}
