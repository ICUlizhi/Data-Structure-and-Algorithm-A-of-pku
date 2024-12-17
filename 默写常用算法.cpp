# include <bits/stdc++.h>
using namespace std;
# define maxn 6

int n;


char s[maxn];
int next[maxn];
void kmp(){
	
}


int w[maxn][maxn]; //已memset(w, 0x3f, sizeof(w));且连边的数据已加载
int dis[maxn],vis[maxn];
void dij(int s){ // 编号为s的点是起点, 所有点的下标范围为1-n
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
}

int g[maxn][maxn];
void floyd(){
	
}


int main(){
	
	ios::sync_with_stdio(false);
	// kmp 测试
	cout<<"kmp started"<<endl;
	
	cout<<"kmp finished"<<endl<<endl;
	
	
	// dij 测试, 正确的输出中5个距离应该是 0,2,3,7,6
	cout<<"dij started"<<endl;
	memset(w, 0x3f, sizeof(w));
    w[1][2] = 2; w[1][3] = 4;
    w[2][3] = 1; w[2][4] = 7;
    w[3][5] = 3;
    w[4][5] = 1;
    n=5;
    cout << "顶点数: " << 5 << endl;
    cout << "起点到其他顶点的最短距离为:" << endl;
    int start = 1; // 起点
    dij(start); // 调用 Dijkstra 算法
    for (int i = 1; i <= n; i++) {
        if (dis[i] == 0x3f) // 判断无穷大
            cout << "顶点 " << i << ": 无法到达" << endl;
        else
            cout << "顶点 " << i << ": " << dis[i] << endl;
    }
	cout<<"dij finished"<<endl<<endl;
	
	// floyd 测试
	cout<<"floyd started"<<endl;
	
	cout<<"floyd finished"<<endl<<endl;
}