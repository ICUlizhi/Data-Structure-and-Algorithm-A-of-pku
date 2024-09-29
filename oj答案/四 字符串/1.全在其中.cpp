#include <bits/stdc++.h>
using namespace std;

bool isSubsequence(const string &s, const string &t) {
    int s_len = s.length();
    int t_len = t.length();
    int j = 0;

    for (int i = 0; i < s_len && j < t_len; ++i) {
        if (s[i] == t[j]) {
            j++;
        }
    }

    return j == t_len;
}

int main() {
    string s, t;
    while (cin >> t >> s) {
        if (isSubsequence(s, t)) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }
    return 0;
}