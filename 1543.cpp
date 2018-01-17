#include <stdio.h>
#include <string>
#include <iostream>
using namespace std;
int main(void) {
	string T, P;
	getline(cin, T);
	getline(cin, P);
	auto f = T.find(P);
	int cnt = 0;
	while (f != string::npos) {
		cnt++;
		f = T.find(P, f + P.size());
	}
	printf("%d", cnt);
}
