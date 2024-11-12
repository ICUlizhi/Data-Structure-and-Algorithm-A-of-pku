# include<bits/stdc++.h>
using namespace std;

struct dot{
	int x,y,z;
	int i;
	void init(int x0,int y0, int z0,int i0){
		x=x0;y=y0;z=z0;i=i0;
	}
};
struct dotpair{
	dot A,B;
	double dis;
	int i;
	void init(dot A0,dot B0,int i0){
		A = A0;B= B0;i = i0;
		dis = sqrt(pow(B.x-A.x,2)+pow(B.y-A.y,2)+pow(B.z-A.z,2));
	}
	void print(){
		printf ("(%d,%d,%d)-(%d,%d,%d)=",A.x,A.y,A.z,B.x,B.y,B.z);
		cout <<fixed<<setprecision(2)<<dis<<endl;
	}
};
bool awa(dotpair x0, dotpair y0){
	if (x0.dis == y0.dis){
		return (x0.i<y0.i);
	}
	else return (x0.dis > y0.dis);
}
int main(){
	int c;cin >> c;
	dot d[c]; dotpair p[c*(c-1)/2];
	for (int i =0;i<c;i++){
		int l,m,n;cin>>l>>m>>n;
		d[i].init(l,m,n,i);
	}
	int r= 0;
	for (int i=0;i<c;i++){
		for (int j=i+1;j<c;j++){
			p[r].init(d[i],d[j],r);
			r++;
		}
	}
	sort(p,p+c*(c-1)/2,awa);
	r= 0;
	for (int i=0;i<c;i++){
		for (int j=i+1;j<c;j++){
			p[r].print();
			r++;
		}
	}
}