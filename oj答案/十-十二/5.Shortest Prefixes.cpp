#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
const int maxn = 26;
char s[1010][30];
struct Trie
{
	Trie *Next[maxn];
	int cnt;
	Trie()
	{
		cnt = 1;
		memset(Next, NULL, sizeof(Next));
	}
}*root;
void insert(char *str)
{
	int len = strlen(str);
	Trie *p = root, *q;
	for (int i = 0; i < len; i++)
	{
		int id = str[i] - 'a';
		if (p->Next[id] == NULL)
		{
			q = new Trie();
			p->Next[id] = q;
			p = p->Next[id];
		}
		else
		{
			p=p->Next[id];
			(p->cnt)++;
		}
	}
}
void find(char *str)
{
	int len = strlen(str);
	Trie *p = root;
	for (int i = 0; i < len; i++)
	{
		int id = str[i] - 'a';
		p = p->Next[id];
		if (p->cnt > 1)  ///输出这些字符串相同的前缀
		{
			printf("%c", str[i]);
		}
		else   ///当p->cnt==1时，多输出一个字符来唯一的标识这个字符串（本题的关键）      
		{
			printf("%c", str[i]);
			return;
		}
	}
}
int main()
{
	root = new Trie();
	int n = 0;  //模仿别人的博客来进行输入
	while (scanf("%s", s[n])!=EOF)
	{
		insert(s[n]);
		n++;
	}
	for (int i = 0; i < n; i++)
	{
		printf("%s ", s[i]);
		find(s[i]);
		printf("\n");
	}
	return 0;
}
