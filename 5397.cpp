#include <stdio.h>
#include <list>
using namespace std;
int main(void) {
	int T;
	scanf("%d", &T);
	while (T--) {
		char s[1000004];
		scanf("%s", s);
		int i = 0;
		list<char> L;
		auto it = L.begin(); // 현재 커서의 위치(=다음에 삽입될 원소의 위치)
		while (s[i]) {
			if (s[i] == '<') {
				if (it != L.begin())
					it--;
			}
			else if (s[i] == '>') {
				if (it != L.end())
					it++;
			}
			else if (s[i] == '-') {
				if (it != L.begin()) {
					it--;
					it = L.erase(it);
				}
				
			}
			else {
				L.insert(it, s[i]);
			}
			i++;
		}
		it = L.begin();
		while (it != L.end()) {
			printf("%c", *it);
			it++;
		}
		printf("\n");
	}
}
