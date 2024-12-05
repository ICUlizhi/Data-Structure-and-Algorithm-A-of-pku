#include <bits/stdc++.h>

using namespace std;

const int maxn = 50005;

int sz[maxn], n, ch[maxn][2];
long long f[maxn][2];

void dfs(int u) {
  sz[u] = 1;
  if (!ch[u][0]) {
    f[u][0] = f[u][1] = 0;
    return;
  }
  dfs(ch[u][0]), sz[u] += sz[ch[u][0]];
  if (ch[u][1]) {
    dfs(ch[u][1]), sz[u] += sz[ch[u][1]];
    int &l = ch[u][0], &r = ch[u][1];
    f[u][0] = f[l][0] + f[r][0] + abs(sz[l] - sz[r]);
    f[u][1] = min(f[l][0] + f[r][1] + abs(sz[l] - sz[r] + 1), f[l][1] + f[r][0] + abs(sz[l] - sz[r] - 1));
  } else {
    int &v = ch[u][0];
    f[u][0] = f[v][0] + sz[v];
    f[u][1] = f[v][1] + sz[v] - 1;
  }
  return;
}

int main() {
  cin >> n;
  for (int i = 1; i < n; ++i) {
    int a, b; cin >> a >> b;
    if (ch[a][0]) ch[a][1] = b;
    else ch[a][0] = b;
  }
  memset(f, 0x3f, sizeof f);
  dfs(1);
  cout << f[1][1] << endl;
  return 0;
}