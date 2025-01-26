#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e6 + 5;
char S[maxn], P[maxn], T[maxn];
int n, nxt[maxn], match[maxn];
int onepos = -1;

void KMP(char* T, int m, int* match) {
  // 计算出当前答案长度对应的串在原串中的匹配位置
  nxt[0] = -1;
  for (int i = 2, j = 0; i <= m; ++i) {
    while (j && T[j + 1] != T[i]) j = nxt[j];
    if (T[j + 1] == T[i]) ++j;
    nxt[i] = j;
  }
  memset(match, 0, (n + 1) * sizeof(int));
  for (int i = 1, j = 0; i <= n; ++i) {
    while (j && S[i] != T[j + 1]) j = nxt[j];
    if (S[i] == T[j + 1]) ++j;
    if (j == m) {
      match[i - m + 1] = 1;
      j = nxt[j];
    }
  }
}

bool check(int m) {
  for (int i = 1; i <= m; ++i)
    T[i] = S[onepos + i - 1];
  KMP(T, m, match);
  for (int i = 1; i <= n; ++i) if (P[i] == '1' && !match[i]) return false;
  return true;
}

int main() {
  cin >> (S + 1) >> (P + 1);
  n = strlen(S + 1);
  for (int i = 1; i <= n; ++i) {
    if (P[i] == '1') {
      onepos = i;
    }
  }
  if (onepos == -1) {
    // 随便输出
    cout << "ytytest" << '\n';
    return 0;
  }

  int ans = -1, l = 1, r = n - onepos + 1;
  // 二分
  while (l <= r) {
    int mid = (l + r) >> 1;
    if (check(mid)) {
      ans = mid;
      l = mid + 1;
    } else r = mid - 1;
  }

  if (ans == -1) {
    cout << "-1" << endl;
    return 0;
  }

  for (int i = 1; i <= ans; ++i)
    T[i] = S[onepos + i - 1];
  KMP(T, ans, match);

  bool flg = true;
  for (int i = 1; i <= n; ++i) if (P[i] != match[i] + '0') flg = false;
  if (!flg) {
    cout << "-1" << endl;
    return 0;
  }
  for (int i = 1; i <= ans; ++i) putchar(T[i]);
  return 0;
}