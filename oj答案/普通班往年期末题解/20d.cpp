#include <bits/stdc++.h>

using namespace std;

struct Edge {
  int u, v, w;
};
vector<Edge> E;

int fa[27];

int find(int x) {
  return x == fa[x] ? x : fa[x] = find(fa[x]);
}

int main() {
  int n; cin >> n;
  for (int i = 1; i < n; ++i) {
    fa[i] = i;
    char u; cin >> u;
    int c; cin >> c;
    while (c--) {
      char v; cin >> v;
      int w; cin >> w;
      E.push_back({u - 'A' + 1, v - 'A' + 1, w});
    }
  }
  sort(E.begin(), E.end(), [](Edge a, Edge b) {
    return a.w < b.w;
  });
  int ans = 0;
  for (Edge e : E) {
    int u = find(e.u), v = find(e.v);
    if (u != v) {
      fa[u] = v;
      ans += e.w;
    }
  }
  cout << ans << endl;
  return 0;
}