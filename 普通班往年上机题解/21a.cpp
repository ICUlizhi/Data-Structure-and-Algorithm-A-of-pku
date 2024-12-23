#include <bits/stdc++.h>

using namespace std;

string S;

int main() {
  cin >> S;
  int ans = 0;
  stack<int> stk;
  for (char c : S) {
    if (c == '(' || c == '[' || c == '{' || c == '<') stk.push(c);
    else {
      if (stk.empty()) {
        cout << "Impossible" << endl;
        return 0;
      }
      char c2 = stk.top(); stk.pop();
      if (c == ')' && c2 != '(') ++ans;
      if (c == ']' && c2 != '[') ++ans;
      if (c == '}' && c2 != '{') ++ans;
      if (c == '>' && c2 != '<') ++ans;
    }
  }
  if (!stk.empty()) {
    cout << "Impossible" << endl;
    return 0;
  }
  cout << ans << endl;
  return 0;
}