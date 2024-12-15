#include <bits/stdc++.h>

using namespace std;

const int maxn = 205, maxm = 50005;
using ll = long long;
struct Edge {
  int u, v;
  ll a, b;
} e[maxm];
int fa[maxn];
int n, m; ll A, B;

int find(int x) {return x == fa[x] ? x : fa[x] = find(fa[x]);}

int main() {
  ll ans = 1e18;
  cin >> n >> m >> A >> B;
  for (int i = 1; i <= m; ++i) {
    cin >> e[i].u >> e[i].v >> e[i].a >> e[i].b;
  }
  sort(e + 1, e + m + 1, [](const Edge &a, const Edge &b) {
    return a.a < b.a;
  });
  vector<int> candidate;
  for (int i = 1; i <= m; ++i) {
    vector<int> tmp;
    candidate.push_back(i);
    for (int j = 1; j <= n; ++j) fa[j] = j;
    ll maxb = 0;
    sort(candidate.begin(), candidate.end(), [](int a, int b) {
      return e[a].b < e[b].b;
    });
    for (int j : candidate) {
      int u = find(e[j].u), v = find(e[j].v);
      if (u != v) {
        fa[u] = v;
        maxb = e[j].b;
        tmp.push_back(j);
      }
    }
    if (tmp.size() == n - 1)
      ans = min(ans, A * e[i].a + B * maxb);
    tmp.swap(candidate);
  }
  cout << ans << endl;
  return 0;
}