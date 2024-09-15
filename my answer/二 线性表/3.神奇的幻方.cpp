# include <bits/stdc++.h>
using namespace std;



int main(){
	int n;cin>>n;
	int l = 2*n-1;
	vector <vector <int>> a(l, vector<int>(l,0));
	int x=0,y=n-1;
	for(int i=1;i<=l*l;i++){
		a[x][y]=i;//cout<<i<<"is in : "<<x<<' '<<y<<endl;
		int x0=(x-1+l)%l,y0=(y+1+l)%l;
		if(a[x0][y0]!=0){
			x0=(x+1)%l;
			y0=y;
		}
		x=x0;y=y0;
	}
	
	for (int i=0;i<l;i++){
		for (int j=0;j<l;j++){
			cout << a[i][j]<<' ';
		}
		cout<<endl;
	}
}