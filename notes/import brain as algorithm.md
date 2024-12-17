堆栈 : 
字符串 : KMP算法
二叉树 : 
树 : 
图 : dijkstra算法, floyd算法, Kruskal算法
排序 : 归并
检索 : 

- 所有的算法只包含尽可能简化的模版, 不记录数据, 但会做预处理

1. KMP算法
```cpp
//s[1] 对齐第一个字符, s[n] 是最后一个字符, next[i]是第i个字符的前缀后缀最长匹配长度
next[1] = 0; 
for (int i=2,j=0;i<=n;i++){
    while (j && s[i]!=s[j+1]) j = next[j]; // 一直往前找, 直到找到一个匹配的或者j=0
    if (s[i]==s[j+1])j++; // 找到了一个匹配的
    next[i] = j; // 保存匹配长度
}
```

2. dijkstra算法 (用堆实现)
```cpp
int dis[N], vis[N] = {}; // 起点到i的最短距离, 是否已访问过
priority_queue<pair<int, int>, vector <pair<int, int>>, greater<pair<int, int>>> q;
// first 是距离，second 是点的编号
void dijkstra(int s){
    memset(dis, 0x3f, sizeof(dis)); // 初始化距离为无穷大
    dis[s] = 0; // 起点到自己的距离为0
    q.push({0, s}); // 起点入队
    while (!q.empty()){
        int u = q.top().second; // 取出队列中的最小值
        q.pop(); // 弹出
        if (vis[u]) continue; // 如果已经访问过，跳过
        vis[u] = 1; // 标记为已访问
        for (auto e : G[u]){ // 遍历所有与u相连的边
            int v = e.first, w = e.second; // v 是另一个点，w 是边的权重
            dis[v] = min(dis[v], dis[u] + w); // 更新最短距离
            q.push({dis[v], v}); // 将v放入队列
            }
        }
    }
}
```

3. floyd算法
```cpp
memset(g, 0x3f, sizeof(g));
g[i][i] = 0;
for (int k=1;k<=n;k++)
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++)
            g[i][j] = min(g[i][j],g[i][k]+g[k][j]);
```


4. Kruskal算法
```cpp
struct Edge {
    int u, v, w;  // u, v: 两个节点，w: 边的权重
};
vector<Edge> E;  // 存储所有的边
int fa[114514];  // 用于并查集的父节点数组
int find(int x) { // 查找函数，路径压缩优化
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}
void Kruskal(){
    for (int i = 0; i < 114514; i++) {  // 初始化并查集
        fa[i] = i;
    }
    sort(E.begin(), E.end(), [](Edge a, Edge b) { 
        return a.w < b.w;
    });// 按照边的权重升序排序
    for (Edge e : E) {
        int u = find(e.u), v = find(e.v);  // 查找 u, v 的
        if (u != v) fa[u] = v; // 若没有形成环, 则合并
    }
}
```

5. 归并排序
```cpp
void merge_sort(int l, int r){
    if (l == r) return; // 递归边界
    int mid = (l + r) >> 1; // 取中点
    merge_sort(l, mid); // 递归排序左半部分
    merge_sort(mid + 1, r); // 递归排序右半部分
    int i = l, j = mid + 1, k = 0; // i, j 分别指向左右两部分的起点, k 用于合并
    while (i <= mid && j <= r) { // 合并两部分
        if (a[i] <= a[j]) b[k++] = a[i++];
        else b[k++] = a[j++];
    }
    while (i <= mid) b[k++] = a[i++]; // 处理剩余部分
    while (j <= r) b[k++] = a[j++];
    for (int i = l; i <= r; i++) a[i] = b[i - l]; // 将合并后的数组复制回原数组
}
```

Trick1:
```cpp
ios::sync_with_stdio(false); // 关闭输入输出流的同步，加快cincout速度
```