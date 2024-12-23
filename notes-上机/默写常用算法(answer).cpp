# include <bits/stdc++.h>
using namespace std;
# define maxn 6

int n;


char s[maxn];
int nxt[maxn];
void kmp(){
	//TODO
	nxt[1] = 0;
	for (int i=2,j=0;i<=n;i++){
		while(j&&s[i]!=s[j+1]) j=nxt[j];
		if(s[i]==s[j+1]) j++;
		nxt[i]=j;
	}
	//ENDTODO
}


int w[maxn][maxn]; //已memset(w, 0x3f, sizeof(w));且连边的数据已加载
int dis[maxn],vis[maxn];
void dij(int s){ // 编号为s的点是起点, 所有点的下标范围为1-n
	//TODO
	priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> q;
	memset(dis,0x3f,sizeof(dis));
	dis [s] = 0;
	q.push({0,s});
	while(!q.empty()){
		int u = q.top().second;
		q.pop();
		if (vis[u])continue;
		vis[u] = 1;
		for (int i=1;i<=n;i++){
			int w0 = min(w[i][u],w[u][i]);
			dis[i] = min(dis[i],dis[u]+w0);
			q.push({dis[i],i});
		}
	}
	//ENDTODO
}

int g[maxn][maxn]; //已memset(g, 0x3f, sizeof(g));且连边的数据已加载
void floyd(){
	//TODO
	for(int i=1;i<=n;i++) g[i][i]=0;
	for(int k=1;k<=n;k++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				g[i][j] = min(g[i][j],g[i][k]+g[k][j]);
				g[j][i] = g[i][j];
			}
		}
	}
	//ENDTODO
}

bool check(int x) { 
	return x * x <= 100;
}// 判断 x 是否满足条件
int binarySearch(int left, int right) {
	//TODO
	if (check(right)) return right; // 如果 right 满足条件，直接返回 (因为处理不了)
    while (left < right) {
        int mid = left + (right - left) / 2; // 防溢出
        if (check(mid)) left = mid + 1; 
        else right = mid;    
    }
    return left - 1; // 返回符合条件的最大值
	//ENDTODO
}

struct Edge {
    int u, v, w;  // u, v: 两个节点，w: 边的权重
};
vector<Edge> E, Etree;  // E存储边, Etree存储最小生成树的边
int fa[114514];  // 用于并查集的父节点数组
int find(int x) { // 查找函数，路径压缩优化
	//TODO
    return x == fa[x] ? x : fa[x] = find(fa[x]);
	//ENDTODO
}
void Kruskal(){
	//TODO
    for (int i = 1; i <= n; i++) {  // 初始化并查集
        fa[i] = i;
    }
    sort(E.begin(), E.end(), [](Edge a, Edge b) { 
        return a.w < b.w;
    });// 按照边的权重升序排序
    for (Edge e : E) {
        int u = find(e.u), v = find(e.v);  // 查找 u, v 的
        if (u != v) {
			fa[u] = v;  // 合并 u, v
			Etree.push_back(e);  // 将边加入最小生成树
		}
    }
	//ENDTODO
}

int main(){
	
	ios::sync_with_stdio(false);
	// kmp 测试, 正确的输出中next数组应该是 0 0 1 2 3 0 1
	cout<<"kmp started"<<endl;
	strcpy(s+1, "ababaca");
	n = 7;
	cout << "字符串为: " << s + 1 << endl;
	kmp(); // 调用 KMP 算法
	cout << "next 数组为: ";
	for (int i = 1; i <= n; i++)
		cout << nxt[i] << " ";
	cout << endl;
	cout<<"kmp finished"<<endl<<endl;
	
	
	// dij 测试, 正确的输出中5个距离应该是 0,2,3,7,6
	cout<<"dij started"<<endl;
	memset(w, 0x3f, sizeof(w));
    w[1][2] = 2; w[1][3] = 4;
    w[2][3] = 1; w[2][4] = 7;
    w[3][5] = 3;
    w[4][5] = 1;
    n=5;
    int start = 1; // 起点
    dij(start); // 调用 Dijkstra 算法
    for (int i = 1; i <= n; i++) {
		cout << dis[i] << ' ';
    }
	cout<<"dij finished"<<endl<<endl;
	
	// floyd 测试, 正确的输出中距离应该是 0,2,3,7,6,2...
	cout<<"floyd started"<<endl;
	memset(g, 0x3f, sizeof(g));
	g[1][2] = 2; g[1][3] = 4;
	g[2][3] = 1; g[2][4] = 7;
	g[3][5] = 3;
	g[4][5] = 1;
	n=5;
	floyd(); // 调用 Floyd 算法
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cout << g[i][j] << ' ';
		}
	}
	cout<<"floyd finished"<<endl<<endl;

	//二分法测试, 正确的输出中应该是 10, 10, 10
	cout<<"binarySearch started"<<endl;
	cout<<binarySearch(1,100)<<endl;
	cout<<binarySearch(1,10)<<endl;
	cout<<binarySearch(10,100)<<endl;
	cout<<"binarySearch finished"<<endl<<endl;

	//Kruskal测试, 正确的输出中应该是 3,4,5,9
	cout<<"Kruskal started"<<endl;
	E.push_back({1, 2, 3});
	E.push_back({1, 3, 4});
	E.push_back({1, 4, 5});
	E.push_back({2, 3, 6});
	E.push_back({2, 4, 7});
	E.push_back({3, 4, 8});
	E.push_back({3, 5, 9});
	E.push_back({4, 5, 10});
	n=5;
	Kruskal();
	//从 fa 中读取最小生成树
	for (Edge e : Etree) {
		cout << e.w << ' ';
	}
	cout<<endl<<"Kruskal finished"<<endl<<endl;
}