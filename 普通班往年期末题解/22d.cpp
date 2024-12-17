#include <bits/stdc++.h>

using namespace std;

char S[100000 + 5][15];

int ch[1000005][26], endid[1000005], tot = 0;

bool getDictionary(int id) {
  static char buf[15];
  char c = getchar();
  if (c == '\n') return false;
  int i = 0;
  while (isalpha(c)) {
    S[id][i++] = c;
    c = getchar();
  }
  S[id][i] = '\0';
  i = 0;
  c = getchar();
  while (isalpha(c)) {
    buf[i++] = c;
    c = getchar();
  }
  buf[i] = '\0';
  int u = 0;
  for (int i = 0; buf[i]; ++i) {
    int v = buf[i] - 'a';
    if (!ch[u][v]) ch[u][v] = ++tot;
    u = ch[u][v];
  }
  endid[u] = id;
  return true;
}

int main() {
  for (int i = 1; getDictionary(i); ++i);
  char s[15];
  while (scanf("%s", s) != EOF) {
    int u = 0;
    for (int i = 0; s[i]; ++i) {
      int v = s[i] - 'a';
      if (!ch[u][v]) break;
      u = ch[u][v];
    }
    if (endid[u]) printf("%s\n", S[endid[u]]);
    else puts("eh");
  }
  return 0;
}