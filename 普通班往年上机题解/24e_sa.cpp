#include <bits/stdc++.h>

using namespace std;

const int maxs = 27, maxn = 2e6 + 5;

int n, m, sa[maxn], id[maxn], rk[maxn], oldrk[maxn], cnt[maxn], ht[maxn];
char S[maxn], P[maxn];

inline bool cmp(int i, int j, int k) {
  return oldrk[i] == oldrk[j] && oldrk[i + k] == oldrk[j + k];
}

bool check(int i, int j, int len) {
  for (int k = 0; k < len && i + k <= n && j + k <= n; ++k) {
    if (S[i + k] != S[j + k]) return false;
  }
  return true;
}

int main() {
  scanf("%s", S + 1);
  n = strlen(S + 1);
  scanf("%s", P + 1);
  m = 26;
  for (int i = 1; i <= n; ++i) ++cnt[rk[i] = S[i] = S[i] - 'a' + 1];
  for (int i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
  for (int i = n; i >= 1; --i) sa[cnt[rk[i]]--] = i;

  for (int w = 1; w < n; w <<= 1) {
    int num = 0;
    for(int i = n - w + 1; i <= n; ++i) id[++num] = i;
    for (int i = 1; i <= n; ++i) if (sa[i] > w) id[++num] = sa[i] - w;
    memset(cnt, 0, sizeof cnt);
    for (int i = 1; i <= n; ++i)++ cnt[rk[id[i]]];
    for (int i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
    for (int i = n; i >= 1; --i) sa[cnt[rk[id[i]]]--] = id[i];
    memcpy(oldrk, rk, sizeof rk);
    num = 0;
    for (int i = 1; i <= n; ++i) rk[sa[i]] = cmp(sa[i], sa[i - 1], w) ? num : ++num;
    m = num;
  }
  for (int i = 1, j = 0; i <= n; ++i) {
    if (j)
      --j;
    while (S[i + j] == S[sa[rk[i] - 1] + j])
      ++j;
    ht[rk[i]] = j;
  }

  vector<int> rks;
  for (int i = 1; i <= n; ++i) {
    if (P[i] == '1') {
      rks.push_back(rk[i]);
    }
  }
  if (rks.empty()) {
    puts("yty");
    return 0;
  }
  sort(rks.begin(), rks.end());
  if (rks.back() - rks.front() + 1 != rks.size()) {
    puts("-1");
    return 0;
  }
  int ans = n;
  for (int i = rks.front() + 1; i <= rks.back(); ++i)
    ans = min(ans, ht[i]);
  if (rks.size() == 1) ans = n - sa[rks.front()] + 1;

  if (rks.back() + 1 <= n && check(sa[rks.back()], sa[rks.back() + 1], ans)) {
    puts("-1");
    return 0;
  }

  for (int i = sa[rks.front()]; i <= min(n, sa[rks.front()] + ans - 1); ++i)
    putchar(S[i] + 'a' - 1);

  return 0;
}