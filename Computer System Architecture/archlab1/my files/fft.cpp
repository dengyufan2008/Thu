#include <cmath>
#include <complex>
#include <fstream>
#define CD complex<double>

using namespace std;

ifstream cin("data1.in");
ofstream cout("data1.out");

const int kMaxN = 4e6 + 1;
const double kPi = acos(-1.0);
int N, m;
CD X[kMaxN], Y[kMaxN], expTable[kMaxN];

int Reverse(int x, int l) {
  int ans = 0;
  for (int i = 0; i < l; i++) {
    ans = (ans << 1) | (x & 1);
    x >>= 1;
  }
  return ans;
}

void FFT() {
  if (N == 1) {
    return;
  } else if (N == 2) {
    CD f0 = X[0], f1 = X[1];
    X[0] = f0 + f1;
    X[1] = f0 - f1;
    return;
  }

  CD *p = X, *q = Y;
  for (int j = 0; j < N; j += 4) {
    int _j = Reverse(j, m), _N = N >> 2;
    CD f0 = p[_j], f1 = p[_j + _N + _N], f2 = p[_j + _N], f3 = p[_j + _N + _N + _N];
    q[j] = f0 + f1 + f2 + f3;
    q[j + 1] = f0 - f1 + (f2 - f3) * CD(0, -1);
    q[j + 2] = f0 + f1 - f2 - f3;
    q[j + 3] = f0 - f1 - (f2 - f3) * CD(0, -1);
  }
  swap(p, q);

  int i = 4;
  for (; i << 1 < N; i <<= 2) {
    int g = 32 / i;
    for (int j = 0; j < N; j += i << 2) {
      int w = 0;
      for (int k = j; k < j + i; k++) {
        CD f0 = p[k], f1 = p[k + i] * expTable[w + w], f2 = p[k + i + i] * expTable[w], f3 = p[k + i + i + i] * expTable[w + w + w & 63];
        if (w + w + w >= 64) {
          f3 = CD(-f3.real(), -f3.imag());
        }
        q[k] = f0 + f1 + f2 + f3;
        q[k + i] = f0 - f1 + (f2 - f3) * CD(0, -1);
        q[k + i + i] = f0 + f1 - f2 - f3;
        q[k + i + i + i] = f0 - f1 - (f2 - f3) * CD(0, -1);
        w += g;
      }
    }
    swap(p, q);
  }

  if (i < N) {
    int g = 64 / i;
    int w = 0;
    for (int k = 0; k < i; k++) {
      CD f0 = p[k], f1 = p[k + i] * expTable[w];
      q[k] = f0 + f1;
      q[k + i] = f0 - f1;
      w += g;
    }
    swap(p, q);
  }

  if (p == Y) {
    for (int i = 0; i < N; i++) {
      q[i] = p[i];
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> N;
  for (int i = 0; i < N; i++) {
    int x, y;
    cin >> x >> y;
    X[i] = CD(x / 8192.0, y / 8192.0);
  }
  for (m = 0; 1 << m < N; m++) {
  }
  for (int i = 0; i < 64; i++) {
    expTable[i] = CD(cos(kPi * -2 / 128 * i), sin(kPi * -2 / 128 * i));
  }
  FFT();
  cout << N << '\n';
  for (int i = 0; i < N; i++) {
    int x = X[i].real() * 8192, y = X[i].imag() * 8192;
    if (x < 0) {
      x += 1LL << 31;
    }
    if (y < 0) {
      y += 1LL << 31;
    }
    cout << x << ' ' << y << '\n';
  }
  return 0;
}
