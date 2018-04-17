#include <stdio.h>
#include <algorithm>
#include <vector>
using namespace std;
typedef pair<int, int> pii;
typedef long long ll;
typedef pair<ll, ll> pll;

#define X first
#define Y second
int N;
vector<ll> acid;
vector<ll> base;
vector<ll> acid_merge_t;
vector<ll> base_merge_t;
vector<ll> acid_merge;
vector<ll> base_merge;
ll val1 = 1000000000, val2 = 1000000000, val3 = 1000000000;
pll find_acid(ll val) {
	for (int i = 0; i < acid.size(); i++) {
		for (int j = i + 1; j < acid.size(); j++) {
			if (acid[i] + acid[j] == val)
				return { acid[i],acid[j] };
		}
	}
	return { -1,-1 };
}
pll find_base(ll val) {
	for (int i = 0; i < base.size(); i++) {
		for (int j = i + 1; j < base.size(); j++) {
			if (base[i] + base[j] == val)
				return { base[j],base[i] };
		}
	}
	return { -1,-1 };
}
int main(void) {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		ll t;
		scanf("%lld", &t);
		if (t > 0)
			acid.push_back(t);
		else
			base.push_back(-t);
	}
	sort(acid.begin(), acid.end());
	sort(base.begin(), base.end());
	if (acid.size() >= 3) {
		if (abs(val3 + val2 + val1) > acid[0] + acid[1] + acid[2])
			val1 = acid[0], val2 = acid[1], val3 = acid[2];
	}
	if (base.size() >= 3) {
		if (abs(val3 + val2 + val1) > base[0] + base[1] + base[2])
			val1 = -base[2], val2 = -base[1], val3 = -base[0];
	}
	if (acid.empty() || base.empty()) {
		printf("%lld %lld %lld", val1, val2, val3);
		return 0;
	}
	for (int i = 0; i < acid.size(); i++)
		for (int j = i + 1; j < acid.size(); j++)
			acid_merge_t.push_back(acid[i] + acid[j]);
	for (int i = 0; i < base.size(); i++)
		for (int j = i + 1; j < base.size(); j++)
			base_merge_t.push_back(base[i] + base[j]);

	sort(acid_merge_t.begin(), acid_merge_t.end());
	sort(base_merge_t.begin(), base_merge_t.end());

	if (!base_merge_t.empty()) {
		base_merge.push_back(base_merge_t[0]);
		for (int i = 1; i < base_merge_t.size(); i++)
			if (base_merge_t[i] != base_merge_t[i - 1])
				base_merge.push_back(base_merge_t[i]);
		for (ll a : acid) {
			auto t = lower_bound(base_merge.begin(), base_merge.end(), a);
			if (t != base_merge.begin()) {
				if (abs(val3 + val2 + val1) > abs(a - *(t - 1))) {
					pll tmp = find_base(*(t - 1));
					val1 = -tmp.X, val2 = -tmp.Y, val3 = a;
				}
			}
			if (t != base.end()) {
				if (abs(val3 + val2 + val1) > abs(a - *t)) {
					pll tmp = find_base(*t);
					val1 = -tmp.X, val2 = -tmp.Y, val3 = a;
				}
			}
		}
	}
	if (!acid_merge.empty()) {
		acid_merge.push_back(acid_merge_t[0]);
		for (int i = 1; i < acid_merge_t.size(); i++)
			if (acid_merge_t[i] != acid_merge_t[i - 1])
				acid_merge.push_back(acid_merge_t[i]);
		for (ll b : base) {
			auto t = lower_bound(acid_merge.begin(), acid_merge.end(), b);
			if (t != acid_merge.begin()) {
				if (abs(val3 + val2 + val1) > abs(b - *(t - 1))) {
					pll tmp = find_acid(*(t - 1));
					val1 = -b, val2 = tmp.X, val3 = tmp.Y;
				}
				if (t != base.end()) {
					if (abs(val3 + val2 + val1) > abs(b - *t)) {
						pll tmp = find_acid(*t);
						val1 = -b, val2 = tmp.X, val3 = tmp.Y;
					}
				}
			}
		}
	}
	printf("%lld %lld %lld", val1, val2, val3);
}
