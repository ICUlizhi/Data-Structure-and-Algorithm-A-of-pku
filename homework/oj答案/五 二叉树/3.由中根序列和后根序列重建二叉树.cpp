#include <bits/stdc++.h>
using namespace std;
#define N 65536
 
struct node{
    int data;
    struct node * lc,*rc;
}BitNode,*BitTree;
 
int sLDR[N],sLRD[N];
int tree[N];
 
 
void BuildTree(int coStart,int coEnd,int loStart, int loEnd,int k){
    //BitTree root = (BitTree)malloc(sizeof(BitNode));
    tree[k] = sLRD[loEnd];
    tree[2*k] = 0;
    tree[2*k+1] = 0;
    //root->lc = NULL;
    //root->rc = NULL;
    int i;
 
    if(coStart == coEnd)
        return ;
    for(i = 0;i <= coEnd-coStart;i++){
        if(sLDR[coStart+i] == sLRD[loEnd])
            break;
    }
 
    if(i>=1) BuildTree(coStart,coStart+i-1,loStart,loStart+i-1,2*k);
    if(coEnd>=coStart+i+1) BuildTree(coStart+i+1,coEnd,loStart+i,loEnd-1,2*k+1);
    //return root;
}
 
int visit(int i){
    printf("%d ",tree[i]);
    return tree[i];
}
 
int PreTranverse(int i){
    if(tree[i]){
        visit(i);
        if(tree[2*i])
            PreTranverse(2*i);
        if(tree[2*i+1])
            PreTranverse(2*i+1);
    }
    return 1;
}
 
int main(){
    int s[N];
    int order = 0;
    int ch;
    while((scanf("%d",&ch))!=EOF){
        s[++order] = ch;
    }
    for(int i = 1;i <= order/2;i++)
        sLDR[i] = s[i];
    for(int i = 1;i <= order/2;i++)
        sLRD[i] = s[order/2+i];
    BuildTree(1,order/2,1,order/2,1);
    PreTranverse(1);
    printf("\n");
    return 0;
}