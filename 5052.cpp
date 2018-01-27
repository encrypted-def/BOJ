#include <string>
#include <iostream>
#include <algorithm>
using namespace std;
string arr[10005];
bool isPrefix(string a, string b) {
	if (a.size() >= b.size())
		return false;
	for (int i = 0; i < a.size(); i++)
		if (a[i] != b[i])
			return false;
	return true;
}
int main(void) {
	ios::sync_with_stdio(false);
	int T;
	cin >> T;
	while (T--) {
		int n;
		cin >> n;
		for(int i = 0; i < n; i++)
			cin >> arr[i];
		sort(arr, arr + n);
		bool isConsistent = true;
		for (int i = 0; i < n - 1; i++) {
			if (isPrefix(arr[i], arr[i + 1])) {
				isConsistent = false;
				break;
			}
		}
		if (isConsistent)
			cout << "YES\n";
		else
			cout << "NO\n";
	}
}
