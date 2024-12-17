#include <bits/stdc++.h>
using namespace std;

// 深度优先搜索（DFS）函数，遍历图的一个连通分量
void c(int x, const vector<vector<int>>& a, vector<bool>& b) {//输出当前访问的节点
    b[x] = true; // 标记节点为已访问
    for (auto g : a[x]) {
        if (!b[g]) { // 如果邻接节点未被访问
            c(g, a, b); // 递归DFS调用
        } else {
        }
    }
}

int main() {
    int n, m, _case = 1;
    while (cin >> n >> m) {
        if ((n == 0) && (m == 0)) break; 
        vector<vector<int>> a(n+1);
        vector<bool> b(n+1, false);
        int r1, r2;

        // 输入边的信息，并构建无向图
        while (m--) {
            cin >> r1 >> r2;

            a[r1].push_back(r2);
            a[r2].push_back(r1); // 无向图，双向边
        }

        int ans = 0; // 连通分量计数
        for (int i = 1; i < n+1; i++) {
            if (!b[i]) { // 检查节点是否未被访问
                c(i, a, b); // 访问这个分量中的所有节点
                ans++; // 增加连通分量计数
            }
        }

        // 输出每个测试用例的连通分量数量
        cout << "Case " << _case << ": " << ans << endl;
        _case++;
    }
}
