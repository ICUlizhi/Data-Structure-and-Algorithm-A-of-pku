#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e7 + 5;
vector<pair<int, int>> vec;
int stk[maxn], top, n, vis[maxn];

int main() {
  cin >> n;
  int cur = 0;
  for (int i = 1; i <= n; ++i) {
    int x; cin >> x;
    if (vis[x] || x > n) return cout << "NO" << endl, 0;
    while (cur < x) {
      stk[++top] = ++cur;
      vec.push_back({1, cur});
    }
    if (!top || stk[top] != x) {
      cout << "NO" << endl;
      return 0;
    }
    else {
      vec.push_back({2, stk[top]});
      vis[stk[top--]] = 1;
    }
  }
  for (auto p : vec) {
    if (p.first == 1) cout << "PUSH " << p.second << endl;
    else cout << "POP " << p.second << endl;
  }
  return 0;
}