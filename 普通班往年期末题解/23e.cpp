#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5 + 5;
unordered_map<int, int> G[maxn];

int n, m;

int main() {
  ios::sync_with_stdio(false);
  cin >> n >> m;
  while (m--) {
    int u, v;
    cin >> u >> v;
    G[u][v] = G[v][u] = 1;
  }
  int ans = 0;
  set<int> S;
  for (int i = 1; i <= n; ++i) S.insert(i);
  while (!S.empty()) {
    int u = *S.begin();
    S.erase(u);
    queue<int> q;
    q.push(u);
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      vector<int> remove;
      for (int v : S) {
        if (!G[u][v]) {
          q.push(v);
          remove.push_back(v);
        }
      }
      for (int v : remove) S.erase(v);
    }
    ++ans;
  }
  cout << ans - 1 << endl;
  return 0;
}