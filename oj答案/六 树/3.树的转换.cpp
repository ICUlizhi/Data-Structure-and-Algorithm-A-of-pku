#include <bits/stdc++.h>
using namespace std;
 
const int MAX_NODE = 100005;
 
char s[MAX_NODE*2];
 
int main()
{
    int cnt = 0;
    while (cin.getline(s, MAX_NODE*2)) {
        if (s[0] == '#')
            break;
 
        int n = strlen(s);
        int d = 0;
        int tree_dep = 0, btree_dep = 0;
 
        /* general tree */
        for (int i = 0; i < n; ++i) {
            int add = s[i] == 'd' ? 1 : -1;
            d += add;
            tree_dep = max(d, tree_dep);
        }
 
        /* binary tree */
        stack<int> fa;
        d = 0;
        for (int i = 0; i < n; ++i) {
            if (s[i] == 'd') {
                fa.push(d);
                d += 1;
            }
            else {
                if (s[i+1] == 'd')
                    d += 1, ++i;
                else {
                    d = fa.top();
                    fa.pop();
                }
            }
            btree_dep = max(d, btree_dep);
        }
 
        /* print result */
        printf("Tree %d: %d => %d\n", ++cnt, tree_dep, btree_dep);
    }

    return 0;
}