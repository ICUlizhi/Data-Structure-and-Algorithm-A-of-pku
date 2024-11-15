# include<bits/stdc++.h>
using namespace std;

const int MAN = 114514;
int _set [MAN] , check [MAN];
int find2(int x){
	int p = x;
	int r = 1;
	while (p!=_set[p]){
		r *= check[p];
		p = _set[p];
	}
	r *= check[p];
	return r;
}
int find(int x){
	if (x!=_set[x]){
		check[x] = find2(x);
		_set[x] = find(_set[x]);
	}
	return _set[x];
}

void _union(int x,int y){
	int xr = find(x);
	int xc = find2(x);
	int yr = find(y);
	int yc = find2(y);
	_set [xr] = yr;
	check [xr] = - xc * yc;
}

int main(){
	int nnn;cin>> nnn;
	while(nnn--){
		int n,m; cin>>n>>m;
		memset (_set, 0, sizeof(_set));
		memset (check, 0, sizeof(check));
		for (int i=1;i<=n;i++){
			_set[i] = i;
			check[i] = 1;
		}
		while (m--){
			char c;int a,b;
			cin >>c>>a>>b;
			if (c=='D'){
				_union (a,b);
			}
			if (c=='A'){
				int ar = find(a), br = find(b);
				int ac = find2(a), bc = find2(b);
				//cout<< a <<ar <<ac<<endl;
				//cout<< b <<br <<bc<<endl;
				if (ar != br) {

					cout<<"Not sure yet."<<endl;
				}	
				else {
					if ( ac*bc == 1) {
						cout<<"In the same gang."<<endl;
					}
					else {
						cout<<"In different gangs."<<endl;
					}
				}
			}
		}
	}
	
}