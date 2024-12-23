#include <bits/stdc++.h>

using namespace std;

int n, m;
map<string, int> id;
string str[35];
int f[35][35];
vector<int> path[35][35];

void printSol(vector<int> v) {
  for (int i = 0; i < v.size(); ++i) {
    cout << str[v[i]];
    if (i + 1 < v.size()) {
      cout << "->(";
      cout << f[v[i]][v[i + 1]];
      cout << ")->";
    }
  }
  cout << endl;
}

int main() {
  cin >> n;
  memset(f, 0x3f, sizeof f);
  for (int i = 1; i <= n; ++i) {
    cin >> str[i];
    id[str[i]] = i;
    f[i][i] = 0;
    path[i][i].push_back(i);
  }
  cin >> m;
  for (int i = 1; i <= m; ++i) {
    string u, v; cin >> u >> v;
    int w; cin >> w;
    f[id[u]][id[v]] = f[id[v]][id[u]] = w;
    path[id[u]][id[v]].push_back(id[u]), path[id[u]][id[v]].push_back(id[v]);
    path[id[v]][id[u]].push_back(id[v]), path[id[v]][id[u]].push_back(id[u]);
  }
  for (int k = 1; k <= n; ++k) {
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= n; ++j) {
        if (f[i][j] > f[i][k] + f[k][j]) {
          f[i][j] = f[i][k] + f[k][j];
          // printf("using %d to %d to %d update %d to %d, %d + %d < %d\n", i, k, j, i, j, f[i][k], f[k][j], f[i][j]);
          // printf("\t");
          // for (int x : path[i][k]) printf("%d ", x); printf("\n\t");
          // for (int x : path[k][j]) printf("%d ", x); puts("");
          path[i][j].clear();
          for (int x : path[i][k])
            path[i][j].push_back(x);
          for (int x : path[k][j])
            if (x != path[i][k].back()) path[i][j].push_back(x);
        }
      }
    }
  }
  int q; cin >> q;
  while (q--) {
    string a, b; cin >> a >> b;
    printSol(path[id[a]][id[b]]);
  }
  return 0;
}