#include <stdio.h>
#include <algorithm>
#include <cmath>
using namespace std;
double f(double x, double y, double d) {
	double sqrt1 = sqrt(x*x - d * d);
	double sqrt2 = sqrt(y*y - d * d);
	return sqrt1 * sqrt2 / (sqrt1 + sqrt2);
}
int main(void) {
	double x, y, c;
	while ((scanf("%lf %lf %lf", &x, &y, &c)) != EOF) {
		double st = 0;
		double en = min(x, y);
		while (en - st > 1e-6) {
			double mid = (st + en) / 2;
			if (f(x, y, mid) > c)
				st = mid;
			else
				en = mid;
		}
		printf("%.3f\n", st);
	}
}
