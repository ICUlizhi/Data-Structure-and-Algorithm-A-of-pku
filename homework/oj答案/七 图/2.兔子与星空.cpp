#include <bits/stdc++.h>
int n, m, fa[200005], Size[200005], cnt = 0;
using namespace std;

struct edge {
	int u, v, w;
};
edge e[5000];

//代表当前已经输入边的数目
int num_e=1;	
//读入一行的数据
void read() {
	char c, c1;
	int u, v, w, t;
	cin >> c >> t;
	u = c - 64;		//将字母转换为数字储存
	while (t--) {
		cin >> c1 >> w;
		v = c1 - 64;
		e[num_e].u = u;
		e[num_e].v = v;
		e[num_e].w = w;
		num_e++;
	}
}

//判断边权重大小
bool cmp(edge x, edge y) {
	return x.w < y.w;
}

int findFather(int x) {
	if (x == fa[x])
		return x;
	else
		return findFather(fa[x]);
}

void Union(int a, int b) {
	int fx = findFather(a);		//寻找a的根结点
	int fy = findFather(b); 	//寻找b的根结点
	if (Size[fx] >= Size[fy]) {
		fa[fy] = fx;
		Size[fx] += Size[fy];
	}
	else {
		fa[fx] = fy;
		Size[fy] -= Size[fx];
	}

}

int main() {
	cin >> n;
	for (int i = 1; i < n; i++) {
		read();
	}
	num_e--;
	for (int i = 1; i <= num_e; i++)
		fa[i] = i, Size[i] = 1;
	//由小到大排序 
	sort(e + 1, e + num_e + 1, cmp);
	long long ans = 0;
	for (int i = 1; i <= num_e; i++) {
		if (findFather(e[i].u) == findFather(e[i].v))
			continue;
		Union(e[i].u, e[i].v);
		cnt++;
		ans += e[i].w;
		if (cnt == n - 1)
			break;
	}
	cout << ans;
	return 0;
}
