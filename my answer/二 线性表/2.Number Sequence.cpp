#include <bits/stdc++.h>
using namespace std;

string a(int n){
	string c;
	int n0=n;
	while (true){
		c+= n0%10+'0';
		n0/=10;
		if(n0==0)break;
	}
	reverse(c.begin(), c.end());
	return c;
}
string b(int n){
	string c;
	for (int i=1;i<=n;i++){
		c+=a(i);
	}
	return c;
}

int num(int n){
	int k=1;int nu=0;int mu=n;
	for(int i=1;i<10;i++){
		if(mu>9*k){
			nu+=9*k*i;
			mu-=9*k;
			k*=10;
		}
		else{
			nu+=(n-k+1)*i;
			break;
		}
	}
	return nu;
}

void ans(int i){
	int c=i;
	for (int j=1;j<1000000;j++){
		//cout<<d;
		int m=num(j);
		if (c<=m){
			string d=b(j);//cout<<j<<','<<d<<',';
			int k = d[c-1]-'0';
			cout<<k<<endl;
			break;
		}
		else{
			c-=m;
		}
	}
	return;
}
int main(){
	int n;cin >> n;
	while (n--){
		int i;cin >> i;
		//cout<<num(i)<<endl;
		ans(i);
		//for (int j=1;j<i;j++){
			//cout<<num(j)<<endl;
			//cout<<"j="<<j<<",";
			//ans(j);
		//}
	} 
	return 0;
}