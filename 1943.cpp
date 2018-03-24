#include <stdio.h>
#include <algorithm>
using namespace std;
typedef pair<int, int> pii;
#define X first
#define Y second
int N;
pii coin[105];
bool D[50004]; // D[i] : i원을 만드는 것이 가능한지.
int main(void) {
	for (int tt = 0; tt < 3; tt++) {
		for (int i = 0; i <= 50000; i++)
			D[i] = false;
		D[0] = true;
		scanf("%d", &N);
		int tot = 0;
		for (int i = 0; i < N; i++) {
			scanf("%d %d", &coin[i].X, &coin[i].Y);
			tot += coin[i].X * coin[i].Y;
		}
		if (tot % 2 == 1) {
			printf("0\n");
			continue;
		}
		sort(coin, coin + N);
		for (int i = 1; i <= coin[0].Y; i++) {
			if (coin[0].X * i > tot / 2)
				break;
			D[i*coin[0].X] = true;
		}
		if (D[tot / 2]) {
			printf("1\n");
			continue;
		}
		bool isPossible = false;
		for (int i = 1; i < N; i++) {
			for (int j = tot/2; j >= 0; j--) {
				if (!D[j])
					continue;
				for (int k = 1; k <= coin[i].Y; k++) {
					if (j + k * coin[i].X > tot / 2)
						break;
					D[j + k * coin[i].X] = true;
				}
				if (D[tot / 2])
					break;
			}
			if (D[tot / 2])
				break;
		}
		printf("%d\n", D[tot / 2]);
	}
}
