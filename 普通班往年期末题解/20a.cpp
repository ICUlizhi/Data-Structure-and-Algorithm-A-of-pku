#include <bits/stdc++.h>

using namespace std;

void solve() {
  unordered_set<int> S;
  int n; scanf("%d", &n);
  while (n--) {
    int x; scanf("%d", &x);
    if (S.count(x)) continue;
    printf("%d ", x);
    S.insert(x);
  }
  return;
}

int main() {
  int T;
  scanf("%d", &T);
  while (T--) solve();
}