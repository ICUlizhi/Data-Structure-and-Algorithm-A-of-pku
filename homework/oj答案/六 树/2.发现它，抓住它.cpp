#include<bits/stdc++.h>
using namespace std;
int n, m, i, j, k = 0, t, w, flag, x, y, z, sum;
string s1, s2, s;
int tree[1000010], relative[1000010];

int head(int x) {
	return x == tree[x] ? x : tree[x] = head(tree[x]);
}

int main() {
	while (cin >> k) {
		while (k--) {
			cin >> n >> m;
			for (i = flag = 0, t = w = -1; i <= n; i++) tree[i] = i, relative[i] = 0;
			for (i = 0; i < m; i++) {
				cin >> s >> x >> y;
				x = head(x); y = head(y);
				if (s == "D") {
					int a = relative[x], b = relative[y];
					if (a) {
						a = head(a);
						if (a != y) tree[a] = y;
					}
					if (b) {
						b = head(b);
						if (b != x) tree[b] = x;
					}
					relative[x] = y; relative[y] = x;
				}
				else {
					if (x == y) cout << "In the same gang." << endl;
					else if (relative[x] == y) cout << "In different gangs." << endl;
					else cout << "Not sure yet." << endl;
				}
			}
		}
	}
}