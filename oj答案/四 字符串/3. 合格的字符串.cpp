#include <bits/stdc++.h>
using namespace std;

bool waw(char a, char b) {
    if (a - 'a' < 26) {
        if (a == b || a + 'A'-'a' == b) return true;
    } else {
        if (a == b || a - 'A'+'a' == b) return true;
    }
    return false;
}

bool awa(const string &s, const string &t) {
    int tl = t.length(), sl = s.length();
    int r = 0;
    for (int i = 0; i < tl; i++) {
        if (t[i] != '[') {
            if (r < sl && waw(t[i], s[r])) {
                r++;
            } else {
                return false;
            }
        } else {
            i++;  // 跳过 '['
            vector<char> options;
            while (t[i] != ']') {
                options.push_back(t[i]);
                i++;
            }
            bool matched = false;
            for (char c : options) {
                if (r < sl && waw(c, s[r])) {
                    r++;
                    matched = true;
                    break;
                }
            }
            if (!matched) return false;
        }
    }
    return r == sl;
}

int main() {
    int n;
    cin >> n;
    vector<string> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }
    string t;
    cin >> t;
    for (int i = 0; i < n; i++) {
        if (awa(s[i], t)) {
            cout << i + 1 << ' ' << s[i] << endl;
        }
    }
    return 0;
}