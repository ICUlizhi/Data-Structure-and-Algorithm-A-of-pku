#include <bits/stdc++.h>
using namespace std;

int f(int m,int n){
	//cout <<m<<','<<n<<endl;
    if(m < n){
    	if(m>0){
			return f(m,m);
		}
		//cout <<"++1"<<endl;
		return 1;	
	}
    if(n == 1){
    	//cout<<"++"<<1<<endl;
    	return 1;
	}
    return f(m-n,n)+f(m,n-1);
}
int main(){
    int n;cin>>n;
    int a,b;
    while(n--){
        cin>>a>>b;
        cout<< f(a,b) <<endl;    
    }
}