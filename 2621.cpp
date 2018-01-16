#include <stdio.h>
#include <algorithm>
using namespace std;
int color_num[4]; // R B Y G
int digit_num[10];
int main(void) {
	int bigNum = 0;
	int pair1 = 0;
	int pair2 = 0;
	int triple = 0;
	int quad = 0;
	for (int i = 0; i < 5; i++) {
		char c;
		int digit;
		scanf(" %c %d", &c, &digit);
		if (c == 'R')
			color_num[0]++;
		else if (c == 'B')
			color_num[1]++;
		else if (c == 'Y')
			color_num[2]++;
		else
			color_num[3]++;
		digit_num[digit]++;
		bigNum = max(bigNum, digit);
	}
	for (int i = 1; i <= 9; i++) {
		if (digit_num[i] == 2) {
			if (pair1 > 0)
				pair2 = i;
			else
				pair1 = i;
		}
		else if (digit_num[i] == 3)
			triple = i;
		else if (digit_num[i] == 4)
			quad = i;
	}
	bool isFlush = false;
	if (color_num[0] == 5 || color_num[1] == 5 || color_num[2] == 5 || color_num[3] == 5)
		isFlush = true;
	bool isStraight = false;
	for (int i = 1; i <= 6; i++) {
		if (digit_num[i] && digit_num[i + 1] && digit_num[i + 2] && digit_num[i + 3] && digit_num[i+4]) {
			isStraight = true;
		}
	}
	if (isFlush && isStraight) {
		printf("%d", 900 + bigNum);
		return 0;
	}
	if (isFlush) {
		printf("%d", 600 + bigNum);
		return 0;
	}
	if (isStraight) {
		printf("%d", 500 + bigNum);
		return 0;
	}
	// Four card check
	if (quad != 0) {
		printf("%d", 800 + quad);
		return 0;
	}
	if (triple != 0 && pair1 != 0) {
		printf("%d", 700 + 10 * triple + pair1);
		return 0;
	}
	if (triple != 0) {
		printf("%d", 400 + triple);
		return 0;
	}
	if (pair1 != 0 && pair2 != 0) {
		printf("%d", 300 + 10 * max(pair1, pair2) + min(pair1, pair2));
		return 0;
	}
	if (pair1 != 0) {
		printf("%d", 200 + pair1);
		return 0;
	}
	printf("%d", 100 + bigNum);
	return 0;
}
