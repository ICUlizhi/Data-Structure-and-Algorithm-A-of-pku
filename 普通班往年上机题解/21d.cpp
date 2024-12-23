#include <bits/stdc++.h>

using namespace std;

const int maxn = 5e4 + 5;
int n, fa[maxn * 3];

int find(int x) {return x == fa[x] ? x : fa[x] = find(fa[x]);}

int main() {
  int k, ans = 0;
  cin >> n >> k;
  for (int i = 1; i <= 3 * n; ++i) fa[i] = i;
  while (k--) {
    int op, x, y; cin >> op >> x >> y;
    if (x > n || y > n) {
      ++ans;
      continue;
    }
    if (op == 1) {
      if (find(x) == find(y + n) || find(x + n) == find(y)) {
        ++ans;
        continue;
      }
      fa[find(x)] = find(y);
      fa[find(x + n)] = find(y + n);
      fa[find(x + 2 * n)] = find(y + 2 * n);
    } else {
      if (find(x) == find(y) || find(x + n) == find(y)) {
        ++ans;
        continue;
      }
      fa[find(x)] = find(y + n);
      fa[find(x + n)] = find(y + 2 * n);
      fa[find(x + 2 * n)] = find(y);
    }
  }
  cout << ans << endl;
  return 0;
}