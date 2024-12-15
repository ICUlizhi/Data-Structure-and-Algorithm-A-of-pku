#include <bits/stdc++.h>

using namespace std;

string dict[10005];
int n;

int check(string &s, string &t, int i, int j, int cur) {
  if (cur > 1) return 2;
  if (i + 1 > (int)s.length() && j + 1 > (int)t.length()) return cur;
  if (i + 1 > (int)s.length()) {
    return check(s, t, i, j + 1, cur + 1);
  }
  if (j + 1 > (int)t.length()) {
    return check(s, t, i + 1, j, cur + 1);
  }
  if (s[i] == t[j]) {
    return check(s, t, i + 1, j + 1, cur);
  }
  else {
    int res1 = check(s, t, i + 1, j, cur + 1);
    if (!res1) return 0;
    int res2 = check(s, t, i + 1, j + 1, cur + 1);
    if (!res2) return 0;
    int res3 = check(s, t, i, j + 1, cur + 1);
    return min(min(res1, res2), res3);
  }
}

int check(string &s, string &t) {
  return check(s, t, 0, 0, 0);
}

void check(string s) {
  vector<int> sim;
  bool same = false;

  for (int i = 1; i <= n; ++i) {
    int res = check(s, dict[i]);
    if (res == 0) same = true;
    else if (res == 1) sim.push_back(i);
    if (same) break;
  }

  if (same) cout << s << " is correct" << endl;
  else {
    cout << s << ": ";
    for (int i : sim) cout << dict[i] << ' ';
    cout << endl;
  }
}

int main() {
  // freopen("a.in", "r", stdin);
  string tmp;
  while (cin >> tmp) {
    if (tmp[0] == '#') break;
    dict[++n] = tmp;
  }
  while (cin >> tmp) {
    if (tmp[0] == '#') break;
    check(tmp);
  }
  return 0;
}