#include <bits/stdc++.h>

using namespace std;

const int maxn = 100000 + 5;
using ll = long long;

int fa[maxn], sz[maxn], n;

int find(int x) {return x == fa[x] ? x : fa[x]  = find(fa[x]);}

struct Edge {
  int u, v, w;
  bool operator < (const Edge &rhs) const {
    return w < rhs.w;
  }
} e[maxn];

int main() {
  cin >> n;
  ll ans = 0;
  for (int i = 1; i <= n; ++i) {
    fa[i] = i, sz[i] = 1;
    if (i < n) {
      cin >> e[i].u >> e[i].v >> e[i].w;
      ans += e[i].w;
    }
  }
  sort(e + 1, e + n);
  for (int i = 1; i < n; ++i) {
    int u = find(e[i].u), v = find(e[i].v);
    ans += 1ll * (e[i].w + 1) * (sz[u] * sz[v] - 1);
    sz[u] += sz[v];
    fa[v] = u;
  }
  cout << ans << endl;
  return 0;
}