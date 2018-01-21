#include <stdio.h>
char gear[4][9];
int idx[4] = { 2,2,2,2 };
int K;
int main(void) {
	for (int i = 0; i < 4; i++)
		scanf("%s", gear[i]);
	scanf("%d", &K);
	while (K--) {
		int a, b;
		scanf("%d %d", &a, &b);
		a--; // index의 편의를 위해 0~3으로 생각a
		bool isTurn[3] = { gear[0][idx[0]] != gear[1][(idx[1]+4)%8], gear[1][idx[1]] != gear[2][(idx[2]+4)%8],gear[2][idx[2]] != gear[3][(idx[3]+4)%8] };
		idx[a] = (idx[a] + 8 - b) % 8;
		if (a == 0) {
			if (isTurn[0]) {
				idx[1] = (idx[1] + 8 + b) % 8;
				if (isTurn[1]) {
					idx[2] = (idx[2] + 8 - b) % 8;
					if (isTurn[2]) {
						idx[3] = (idx[3] + 8 + b) % 8;
					}
				}
			}
		}
		else if (a == 1) {
			if (isTurn[0]) {
				idx[0] = (idx[0] + 8 + b) % 8;
			}
			if (isTurn[1]) {
				idx[2] = (idx[2] + 8 + b) % 8;
				if (isTurn[2]) {
					idx[3] = (idx[3] + 8 - b) % 8;
				}
			}
		}
		else if (a == 2) {
			if (isTurn[1]) {
				idx[1] = (idx[1] + 8 + b) % 8;
				if (isTurn[0]) {
					idx[0] = (idx[0] + 8 - b) % 8;
				}
			}
			if (isTurn[2])
				idx[3] = (idx[3] + 8 + b) % 8;
		}
		else {
			if (isTurn[2]) {
				idx[2] = (idx[2] + 8 + b) % 8;
				if (isTurn[1]) {
					idx[1] = (idx[1] + 8 - b) % 8;
					if (isTurn[0]) {
						idx[0] = (idx[0] + 8 + b) % 8;
					}
				}
			}
		}
	}
	int score = 1 * (gear[0][(idx[0]+6)%8] == '1') + 2 * (gear[1][(idx[1]+6)%8] == '1') + 4 * (gear[2][(idx[2]+6)%8] == '1') + 8 * (gear[3][(idx[3]+6)%8] == '1');
	printf("%d", score);
}
