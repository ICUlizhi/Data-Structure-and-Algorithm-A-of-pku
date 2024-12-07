#include <bits/stdc++.h>

using namespace std;

const int maxn = 5e5 + 5;
int a[maxn], n;

int main() {
  int T; cin >> T;
  while (T--) {
    cin >> n;
    set<int> S;
    bool ans = 0;
    for (int i = 1; i <= n; ++i) {
      cin >> a[i];
      if (i >= 3) if (S.count(a[i])) ans = 1;
      if (i > 1) S.insert(a[i - 1]);
    }
    puts(ans ? "YES" : "NO");
  }
  return 0;
}