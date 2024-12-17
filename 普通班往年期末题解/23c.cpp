#include <bits/stdc++.h>
#define lowbit(x) (x & -x)

using namespace std;

const int maxn = 2e5 + 5;
using ll = long long;
int n, a[maxn], b[maxn], x[maxn << 1];
int t[maxn << 1], tot;

int query(int x) {
  int res = 0;
  for (; x; x -= lowbit(x)) res += t[x];
  return res;
}

void add(int x, int d) {
  for (; x <= tot; x += lowbit(x)) t[x] += d;
  return;
}

int main() {
  cin >> n;
  for (int i = 1; i <= n; ++i) cin >> a[i];
  for (int i = 1; i <= n; ++i) cin >> b[i];
  for (int i = 1; i <= n; ++i) {
    int tmp = a[i] - b[i];
    a[i] = tmp, b[i] = -tmp;
    x[(i << 1) - 1] = a[i], x[i << 1] = b[i];
  }

  sort(x + 1, x + (n << 1) + 1);
  tot = unique(x + 1, x + (n << 1) + 1) - x - 1;
  for (int i = 1; i <= n; ++i) {
    a[i] = lower_bound(x + 1, x + tot + 1, a[i]) - x;
    b[i] = lower_bound(x + 1, x + tot + 1, b[i]) - x;
  }
  ll ans = 0;
  for (int i = n; i >= 1; --i) {
    ans += query(a[i] - 1);
    add(b[i], 1);
  }
  cout << ans << endl;
  return 0;
}