#include <bits/stdc++.h>

using namespace std;

int n;

int main() {
  multiset<int> S1, S2;
  ios::sync_with_stdio(false);
  cin >> n;
  int ans; cin >> ans; cout << ans << '\n';
  for (int i = 3; i <= n; i += 2) {
    int x, y; cin >> x >> y;
    if (x > y) swap(x, y);
    if (y <= ans) {
      S1.insert(x);
      S1.insert(y);

      S2.insert(ans);
      ans = *prev(S1.end());
      S1.erase(prev(S1.end()));

    } else if (x >= ans) {
      S2.insert(x);
      S2.insert(y);

      S1.insert(ans);
      ans = *S2.begin();
      S2.erase(S2.begin());
    } else {
      S1.insert(x);
      S2.insert(y);
    }
    cout << ans << '\n';
  }
  return 0;
}