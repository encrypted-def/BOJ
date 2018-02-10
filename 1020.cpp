#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
typedef long long ll;
ll pow10[16] = { 1,10,100,1000,10000,100000,1000000, 10000000, 100000000, 1000000000, 10000000000,100000000000,1000000000000,10000000000000,100000000000000,1000000000000000 };
int cnt[10] = { 6,2,5,5,4,5,6,3,7,5 };
ll D[17][150]; // D[i][j] : i자리의 합이 j가 되는 가장 작은 수. ex) D[2][6] = 14.(14를 만드는데 선분 6개 필요)
char num[20];
int N;
const ll MX = 0x7f7f7f7f7f7f7f7f;
ll val(char* num, int digit) {
	ll ans = 0;
	for (int i = N - 1; digit--; i--)
		ans += cnt[num[i] - '0'];
	return ans;
}
void inc(char* num, int len) {
	num[N - 1]++;
	for (int i = N - 1; i >= 1; i--) {
		if (num[i] == '0' + 10) {
			num[i] = '0';
			num[i - 1]++;
		}
		else
			return;
	}
	if (num[0] == '0' + 10)
		num[0] = '0';
}
ll diff(char* num, int len, ll val) {
	ll ans = val;
	for (int i = 0; i < len; i++)
		ans -= pow10[i] * (num[N - 1 - i] - '0');
	return ans;
}
int main(void) {
	for (int i = 0; i < 17; i++)
		for (int j = 0; j < 150; j++)
			D[i][j] = MX;
	for (int i = 0; i < 10; i++)
		D[1][cnt[i]] = min(D[1][cnt[i]], (ll)i);
	D[0][0] = 0;
	scanf("%s", num);
	N = strlen(num);
	ll ans = pow10[N]; // 아무리 길어도 10^N번 누르면 제자리로 올테니
	for (int i = 2; i <= 15; i++) {
		for (int msb = 0; msb <= 9; msb++) {
			for (int j = 0; j < 150; j++) {
				if (D[i - 1][j] == MX) continue;
				D[i][j + cnt[msb]] = min(D[i][j + cnt[msb]], D[i - 1][j] + pow10[i - 1] * msb);
			}
		}
	}
	for (int i = 0; i < 10; i++) {
		int last_digit = num[N - 1] - '0';
		if (cnt[i] == cnt[num[N - 1] - '0']) { // 
			if (i > last_digit)
				ans = min(ans, (ll)i - last_digit);
			else if (i == last_digit)
				continue;
			else
				ans = min(ans, (ll)i - last_digit + pow10[N]);
		}
	} // 마지막 자리에 대해서는 그냥 직접 처리
	for (int brute_digit = 2; brute_digit <= N; brute_digit++) { // brute_digit 자리를 0~9로 돌려가면서 ans를 갱신해나갈 것임	
		for (int n = 0; n < 10; n++) {
			// brute_digit 자리가 n일 때
			if (val(num, brute_digit) < cnt[n])
				continue;
			ll mov_val = diff(num, brute_digit, D[brute_digit - 1][val(num, brute_digit) - cnt[n]] + pow10[brute_digit - 1] * n);
			//	printf("n %d mov_val %lld\n", n, mov_val);
			if (mov_val <= 0)
				mov_val += pow10[N];
			ans = min(ans, mov_val);
		}
	}
	printf("%lld\n", ans);

}
