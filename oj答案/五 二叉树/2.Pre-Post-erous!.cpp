#include <bits/stdc++.h>
using namespace std;
 
#define MAXLEN 30
char pre[MAXLEN];
char post[MAXLEN];
 
vector<int> branch_vec;
 
//计算n!
int factorial(int n)
{
	int result=1;
 
	if (n==0) return 1;
	else
	{
		for (int i=1; i<=n; ++i) result *= i;
		return result;
	}
}
 
//计算C(n, m)
int calc_C(int n, int m)
{
	unsigned int tmp=1;
	for (int i=0; i<m; ++i, --n) tmp*=n;
 
	return (tmp/(factorial(m)));
}
 
//计算每一个根结点有多少分支（子树）
void branch_count(int pr1, int pr2, int po1, int po2)	//参数是：preOrder序列的起止下标、postOrder序列的起止下标
{
	int a,b,len, branch=0;
 
	if(pr1==pr2 && po1==po2) return;	//递归出口：这个根结点没有任何子树。
	else
	{
		a=pr1+1;
		b=po1;
		len=0;
 
		while (b<po2)
		{
			while ( (pre[a] != post[b+len]) && (b+len<po2) ) ++len;
		
			++branch;	//每找到一个子树，++branch
			branch_count(a, a+len, b, b+len);	//对这个子树递归执行branch_count
		
			a=a+len+1;
			b=b+len+1;
			len=0;
		}
 
		branch_vec.push_back(branch);	//这个根结点的branch数目存入vector容器
	}
}
 
int main()
{
 
	int m, init_len, ans;
 
	while (1)
	{
		scanf("%d", &m);
		if(m==0) break;
		else
		{
			scanf("%s%s", pre, post);
 
			init_len=strlen(pre);
 
			branch_count(0, init_len-1, 0, init_len-1);
 
			ans=1;
			for (int i=0; i<branch_vec.size(); ++i)
			{
				ans*=(calc_C(m, branch_vec[i]));
			}
 
			printf("%d\n", ans);
 
			branch_vec.clear();
		}
	}
 
	return 0;
}