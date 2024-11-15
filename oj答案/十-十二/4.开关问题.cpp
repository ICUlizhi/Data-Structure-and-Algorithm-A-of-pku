#include<bits/stdc++.h>
using namespace std;
int t, n, x, y, a[100][100], s[100], e[100], b[100];
int cmp(int i, int j) {
    int ai = 0, aj = 0;
    for(int k = n; k > 0; k--) {
        ai += (a[i][k] << (n - k));
        aj += (a[j][k] << (n - k));
    }
    return aj > ai;
}
int main() {
    cin >> t;
    while(t--) {
        cin >> n;
        memset(a, 0, sizeof a);
        for(int i = 1; i <= n; i++)
            cin >> s[i], a[i][i] = 1;
        for(int i = 1; i <= n; i++)
            cin >> e[i], b[i] = s[i] ^ e[i];
        while(cin >> x >> y && (x + y)) {
            a[y][x] = 1;
        }
        int ans = 1;
        for(int i = 1; i <= n; i++) {
            for(int j = i + 1; j <= n; j++)
                if(cmp(i, j)) {
                    for(int k = 1; k <= n; k++)
                        swap(a[i][k], a[j][k]);
                    swap(b[i], b[j]);
                }
            int f = 0;
            for(int j = 1; j <= n; j++) {
                if(a[i][j])
                    f = 1;
            }
            if(f == 0 && b[i] == 1) {
                ans = 0;
                break;
            }
            if(f == 0 && b[i] == 0) {
                ans = (1 << (n - i + 1));
                break;
            }
            for(int k = 1; k <= n; k++)
                if(a[i][k]) {
                    for(int j = 1; j <= n; j++)
                        if(i != j && a[j][k]) {
                            for(int s = 1; s <= n; s++)
                                a[j][s] ^= a[i][s];
                            b[j] ^= b[i];
                        }
                    break;
                }
        }
        if(ans == 0)
            puts("Oh,it's impossible~!!");
        else
            printf("%d\n", ans);
    }
    return 0;
}