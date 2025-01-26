#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e5 + 5;
using ll = long long;
int n;

struct Point {
    ll x, y;
} p[maxn];
ll c0[maxn], d0[maxn];
int c[maxn], d[maxn];

ll t[maxn];

inline int lowbit(int x) {return x & -x;}

void add(int x, int v) {
    for (; x <= n; x += lowbit(x))
        t[x] += v;
    return;
}

ll query(int x) {
    ll res = 0;
    for (; x > 0; x -= lowbit(x)) res += t[x];
    return res;
}

int main() {
    // freopen("c.in", "r", stdin);
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> p[i].x >> p[i].y;
        p[i].y - p[i].x;
        p[i].y + p[i].x;
    }
    sort(p + 1, p + n + 1, [](const Point &a, const Point &b) {
        return a.x < b.x;
    });
    for (int i = 1; i <= n; ++i) {
        c0[i] = c[i] = p[i].y - p[i].x;
        d0[i] = d[i] = p[i].y + p[i].x;
    }
    sort(c0 + 1, c0 + n + 1);
    sort(d0 + 1, d0 + n + 1);
    int totc = unique(c0 + 1, c0 + n + 1) - c0 - 1;
    int totd = unique(d0 + 1, d0 + n + 1) - d0 - 1;
    for (int i = 1; i <= n; ++i) {
        c[i] = lower_bound(c0 + 1, c0 + totc + 1, c[i]) - c0;
        d[i] = lower_bound(d0 + 1, d0 + totd + 1, d[i]) - d0;
        // printf("i %d %d\n", c[i], d[i]);
    }
    ll ans = n * (n - 1ll) / 2;
    ll c1 = 0, c2 = 0;
 
    // 数关于 c 的顺序对，关于 d 的逆序对
    
    for (int i = 1; i <= n; ++i) {
        c1 += query(c[i] - 1);
        add(c[i], 1);
    }
    memset(t, 0, sizeof t);
    for (int i = n; i >= 1; --i) {
        c2 += query(d[i] - 1);
        add(d[i], 1);
    }
    // printf("! %d %d\n", c1, c2);

    cout << ans - c1 - c2 << endl;
    return 0;
}