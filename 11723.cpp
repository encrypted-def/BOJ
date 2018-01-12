#include <stdio.h>
#include <algorithm>
using namespace std;
bool exists[21];
void add(int x) {
	exists[x] = true;
}
void remove(int x) {
	exists[x] = false;
}
int check(int x) {
	return exists[x];
}
void toggle(int x) {
	exists[x] ^= 1;
}
void all(void) {
	fill(exists + 1, exists + 21, true);
}
void empty(void) {
	fill(exists + 1, exists + 21, false);
}
int main(void) {
	int M;
	scanf("%d", &M);
	while (M--) {
		char q[100];
		int x;
		scanf("%s %d", &q, &x);

		if (q[0] == 'a' && q[1] == 'd') add(x);
		else if (q[0] == 'c') printf("%d\n", check(x));
		else if (q[0] == 'r') remove(x);
		else if (q[0] == 't') toggle(x);
		else if (q[0] == 'a' && q[1] == 'l') all();
		else empty();
		
	}
}
