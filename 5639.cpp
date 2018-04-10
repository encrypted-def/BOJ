#include <stdio.h>
#include <algorithm>
using namespace std;
typedef pair<int, int> pii;
#define L first
#define R second
pii sibling[1000005];
void print_recursion(int cur) {
	if (sibling[cur].L != 0)
		print_recursion(sibling[cur].L);
	if (sibling[cur].R != 0)
		print_recursion(sibling[cur].R);
	printf("%d\n", cur);
}
int main(void) {
	int root;
	scanf("%d", &root);
	int t;
	while (scanf("%d", &t) != EOF) {
		int st = root;
		while (true) {
			if (t < st) {
				if (sibling[st].L == 0) {
					sibling[st].L = t;
					break;
				}
				else
					st = sibling[st].L;
			}
			if (t > st) {
				if (sibling[st].R == 0) {
					sibling[st].R = t;
					break;
				}
				else
					st = sibling[st].R;
			}
		}
	}
	print_recursion(root);
}
