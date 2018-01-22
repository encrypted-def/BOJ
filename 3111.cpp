#include <stdio.h>
#include <string.h>
#include <list>
using namespace std;
char A[30];
char T[300003];
list<char> L;
int lenA = 0;
int lenT = 0;
bool stringCmp(list<char>* L, list<char>::iterator it) {
	for (int i = 0; i < lenA; i++) {
		if (it == L->end())
			return false;
		if (*it != A[i])
			return false;
		it++;
	}
	return true;
}
bool stringCmp_Reverse(list<char>* L, list<char>::iterator it) {
	for (int i = lenA - 1; i >= 0; i--) {
		if (it == L->begin())
			return false;
		if (*it != A[i])
			return false;
		it--;
	}
	return true;
}
int main(void) {
	scanf("%s", &A);
	scanf("%s", &T);
	lenA = strlen(A);
	lenT = strlen(T);
	for (int i = 0; i < lenT; i++)
		L.push_back(T[i]);
	L.push_front('-'); // 절대 나올 수 없는 문자를 앞, 뒤에 넣어둠
	L.push_back('=');
	auto it1 = L.begin(); // iterator
	auto it2 = L.end(); // reverse_interator
	bool dir = false; // true : 앞쪽에서부터 false : 뒷쪽에서부터
	int cnt = 0;
	while (true) {
		if (dir) {
			if (it1 == L.end())
				break;
			if (stringCmp(&L, it1)) {
				for (int i = 0; i < lenA; i++)
					it1 = L.erase(it1); // 문자열이 찾아졌으면 제거
				for (int i = 0; i < 2 * lenA; i++) { // 제거됨으로서 문자열이 새롭게 생길 수 있으므로 it1을 2*lenA만큼 후퇴시킴
					if (it1 == L.begin())
						break;
					it1--;
				}
				dir = false; // 방향 수정
			}
			else
				it1++;
		}
		else {
			if (it2 == L.begin())
				break;
			if (stringCmp_Reverse(&L, it2)) {
				for (int i = 0; i < lenA; i++) {
					it2 = L.erase(it2);
					it2--;
				}
				for (int i = 0; i < 2 * lenA; i++) {
					if (*it2 == '=')
						break;
					it2++;
				}
				dir = true;
			}
			else
				it2--;
		}
	}
	L.pop_front();
	L.pop_back(); // 끼워뒀던 두 문자를 제거
	for (auto elem : L)
		printf("%c", elem);
}
