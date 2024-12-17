#include <bits/stdc++.h>
using namespace std;


int n0, n;

int main(){
	cin>>n0;
	while(n0--){
		cin>>n;
		priority_queue<int, vector<int>, greater<int> > q;
		int c;
		for(int i=0;i<n;i++){
			cin>>c;q.push(c);
		}
		int ans = 0;
		for(int i=0;i<n-1;i++){
			int x1=q.top();q.pop();
			int x2=q.top();q.pop();
			ans += x1+x2;
			//cout<< "x1 " << x1 << "x2 "<<x2 <<endl;
			q.push(x1+x2);
		}
		cout<<ans<<endl;
	}
}