#include <math.h>
#include <complex>
#include <vector>
#include <algorithm>
using namespace std;
#define M_PI 3.14159265358979323846
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(),(v).end()
typedef complex<double> base;

void fft(vector <base> &a, bool invert)
{
	int n = sz(a);
	for (int i = 1, j = 0; i<n; i++) {
		int bit = n >> 1;
		for (; j >= bit; bit >>= 1) j -= bit;
		j += bit;
		if (i < j) swap(a[i], a[j]);
	}
	for (int len = 2; len <= n; len <<= 1) {
		double ang = 2 * M_PI / len*(invert ? -1 : 1);
		base wlen(cos(ang), sin(ang));
		for (int i = 0; i<n; i += len) {
			base w(1);
			for (int j = 0; j<len / 2; j++) {
				base u = a[i + j], v = a[i + j + len / 2] * w;
				a[i + j] = u + v;
				a[i + j + len / 2] = u - v;
				w *= wlen;
			}
		}
	}
	if (invert) {
		for (int i = 0; i<n; i++) a[i] /= n;
	}
}

void multiply(const vector<int> &a, const vector<int> &b, vector<int> &res)
{
	vector <base> fa(all(a)), fb(all(b));
	int n = 1;
	while (n < max(sz(a), sz(b))) n <<= 1;
	fa.resize(n); fb.resize(n);
	fft(fa, false); fft(fb, false);
	for (int i = 0; i<n; i++) fa[i] *= fb[i];
	fft(fa, true);
	res.resize(n);
	for (int i = 0; i<n; i++) res[i] = int(fa[i].real() + (fa[i].real()>0 ? 0.5 : -0.5));
}

int main(void) {
	int N;
	vector<int> X, Y;
	vector<int> S;
	scanf("%d", &N);
	X.resize(2*N);
	Y.resize(N);
	for (int i = 0; i < N; i++) {
		scanf("%d", &X[i]);
		X[i + N] = X[i];
	}
	for (int i = 0; i < N; i++)
		scanf("%d", &Y[N-1-i]);
	multiply(X, Y, S);
	int mx = -1;
	for (int i = N; i < 2 * N; i++)
		mx = max(mx, S[i]);
	printf("%d", mx);
}
