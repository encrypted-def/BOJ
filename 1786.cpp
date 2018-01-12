#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

int fail[1000004];
string T;
string P;
int lenT, lenP;
int main(void) {
	getline(cin, T);
	getline(cin, P);
	lenT = T.size();
	lenP = P.size();
	int cmp = 0;
	for (int i = 1; i < lenP; i++) {
		while (cmp > 0 && P[i] != P[cmp])
			cmp = fail[cmp-1];
		if (P[i] == P[cmp])
			fail[i] = ++cmp;
	}
	vector<int> ans;
	cmp = 0;
	for (int i = 0; i < lenT; i++) {
		while (cmp > 0 && T[i] != P[cmp])
			cmp = fail[cmp - 1];
		if (T[i] == P[cmp]) {
			if (cmp == lenP - 1) {
				ans.push_back(i - cmp + 1);
				cmp = fail[cmp];
			}
			else
				cmp++;
		}
	}
	printf("%d\n", ans.size());
	for (auto i : ans)
		printf("%d ", i);	
}
