#include <iostream>
#include <cstring>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

const int INF = 0x3f3f3f3f;

map<string, int> q;
map<int, string> p;
int mapp[100][100];
int vis[10010];
int low[5000];
int path[100010];
int re[10010];
int n, m, r;
string s1, s3, s2, s4, str;

void dijkstra(int x) {
    memset(vis, 0, sizeof(vis));
    memset(path, 0, sizeof(path));

    for (int i = 1; i <= n; i++) {
        low[i] = INF;
        path[i] = x;
    }
    low[x] = 0;

    for (int i = 1; i <= n; i++) {
        int u = -1;
        for (int j = 1; j <= n; j++) {
            if ((u == -1 || low[j] < low[u]) && vis[j] == 0) {
                u = j;
            }
        }
        vis[u] = 1;
        for (int k = 1; k <= n; k++) {
            if (vis[k] == 0 && low[k] > low[u] + mapp[u][k]) {
                low[k] = low[u] + mapp[u][k];
                path[k] = u;
            }
        }
    }
}

int main() {
    while (scanf("%d", &n) != EOF) {
        q.clear();
        memset(re, 0, sizeof(re));
        for (int i = 0; i < 100; i++)
            for (int j = 0; j < 100; j++) {
                if (i == j)
                    mapp[i][j] = 0;
                else
                    mapp[i][j] = INF;
            }
        
        for (int i = 1; i <= n; i++) {
            cin >> str;
            q[str] = i;
            p[i] = str;
        }

        scanf("%d", &m);
        while (m--) {
            int c;
            cin >> s1 >> s2 >> c;
            mapp[q[s1]][q[s2]] = mapp[q[s2]][q[s1]] = c;
        }

        scanf("%d", &r);
        while (r--) {
            cin >> s3 >> s4;
            if (s3 == s4)
                cout << s3 << endl;
            else {
                dijkstra(q[s3]);
                int v = 0;
                int keep = q[s4];
                int keep2 = q[s3];
                while (keep != q[s3]) {
                    re[v++] = keep;
                    keep = path[keep];
                }
                re[v++] = q[s3];
                for (int i = v - 1; i > 0; i--) {
                    cout << p[re[i]] << "->(" << mapp[re[i]][re[i - 1]] << ")->";
                }
                cout << s4 << endl;
            }
        }
    }
    return 0;
}
