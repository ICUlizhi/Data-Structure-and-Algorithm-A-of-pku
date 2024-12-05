#include <bits/stdc++.h>

using namespace std;

int n, m, k;

struct Edge {
  int u, v, w;
} e[2005];
struct Edge1 {
  int to, w;
};

vector<Edge1> G[1005];
int dis[1005], vis[1005];

bool check(int mid) {
  for (int i = 1; i <= n; ++i) vector<Edge1>().swap(G[i]);
  for (int i = 1; i <= m; ++i) {
    if (e[i].w <= mid) G[e[i].u].push_back({e[i].v, 0}), G[e[i].v].push_back({e[i].u, 0});
    else G[e[i].u].push_back({e[i].v, 1}), G[e[i].v].push_back({e[i].u, 1});
  }
  memset(dis, 0x3f, sizeof(dis));
  memset(vis, 0, sizeof(vis));
  deque<int> q;
  q.push_back(1);
  dis[1] = 0;
  while (!q.empty()) {
    int u = q.front();
    q.pop_front();
    if (vis[u]) continue;
    vis[u] = 1;
    for (auto e : G[u]) {
      if (vis[e.to]) continue;
      if (dis[e.to] > dis[u] + e.w) {
        dis[e.to] = dis[u] + e.w;
        if (e.w == 0) q.push_front(e.to);
        else q.push_back(e.to);
      }
    }
  }
  return dis[n] <= k;
}

int main() {
  cin >> n >> m >> k;
  int l = 0, r = 0;
  for (int i = 1; i <= m; ++i) {
    cin >> e[i].u >> e[i].v >> e[i].w;
    r = max(r, e[i].w);
  }
  int ans = -1;
  while (l < r) {
    int mid = (l + r) >> 1;
    if (check(mid)) {
      ans = mid;
      r = mid;
    } else l = mid + 1;
  }
  cout << ans << endl;
  return 0;
}