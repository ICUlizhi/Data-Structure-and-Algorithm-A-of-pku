#include <bits/stdc++.h>

using namespace std;

struct Point {
  int x, y, z;
} p[11];

struct Pair {
  int a, b;
  long long dst2;
} pp[200];

int n;

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> p[i].x >> p[i].y >> p[i].z;
  }
  int cnt = 0;
  for (int i = 1; i <= n; ++i) for (int j = i + 1; j <= n; ++j) {
    ++cnt;
    pp[cnt].a = i, pp[cnt].b = j;
    pp[cnt].dst2 = 1ll * (p[i].x - p[j].x) * (p[i].x - p[j].x) + 1ll * (p[i].y - p[j].y) * (p[i].y - p[j].y) + 1ll * (p[i].z - p[j].z) * (p[i].z - p[j].z);
  }
  sort(pp + 1, pp + cnt + 1, [](Pair a, Pair b) {
    return a.dst2 == b.dst2 ? a.a == b.a ? a.b < b.b : a.a < b.a : a.dst2 > b.dst2;
  });
  for (int i = 1; i <= cnt; i++) {
    printf("(%d,%d,%d)-(%d,%d,%d)=%.2lf\n", p[pp[i].a].x, p[pp[i].a].y, p[pp[i].a].z, p[pp[i].b].x, p[pp[i].b].y, p[pp[i].b].z, sqrt(pp[i].dst2));
  }
  return 0;
}