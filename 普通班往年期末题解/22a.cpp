#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5 + 5;
int nxt[maxn];
char s[maxn];
int n;

int main() {
  scanf("%s", s + 1);
  n = strlen(s + 1);
  nxt[1] = 0;
  for (int i = 2, j = 0; i <= n; ++i) {
    while (j && s[i] != s[j + 1]) j = nxt[j];
    if (s[i] == s[j + 1]) ++j;
    nxt[i] = j;
  }
  int cycle = n - nxt[n];
  if (n % cycle == 0) {
    if (n == cycle) cout << cycle << endl;
    else cout << 0 << endl;
  } else cout << cycle - n % cycle << endl;
  return 0;
}