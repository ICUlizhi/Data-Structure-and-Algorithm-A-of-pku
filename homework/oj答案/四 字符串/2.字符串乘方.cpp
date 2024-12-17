#include <bits/stdc++.h>

using namespace std;
void kmp(char *s, int *next, int len){
    int k1=-1;
    int k2=0;
    next[0]=-1;
    while(k2!=len){
        while(k1>=0&&s[k1]!=s[k2]){
            k1=next[k1];
        }
        k1++;
        k2++;
        next[k2]=k1;
    }
}
int main(){
    char s[1000000];
    while(scanf("%s",s)&&s[0]!='.'){
        int len=strlen(s);
        int next[len+1];
        kmp(s,next,len);
        int ans=len-next[len];
        printf("%d\n",len%ans==0?len/ans:1);
    }
}