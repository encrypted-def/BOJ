#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1e9 + 7;
ll ppow2[300003];
int main(void) {	
	ios::sync_with_stdio(false);
	cin.tie(0);
	int N;
	cin >> N;
	vector<ll> val(N + 1);
	for(int i = 1; i <= N; i++) {
		cin >> val[i];
	}
	sort(val.begin()+1,val.end());
	ppow2[0] = 1;
	for(int i = 1; i <= N; i++) {
		ppow2[i] = (ppow2[i - 1] * 2) % MOD;
	}
	ll ans = 0;
	for(int i = 1; i <= N; i++)
		ans = (ans+ (ppow2[i - 1] - ppow2[N-i]) * val[i])%MOD;
	if (ans < 0) ans += MOD;
	cout << ans;
}
