#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
int a[10];
int p[105];
int s[5];
int m=12500000;
short y[25000005];
int main() {
	for(int i=-50; i<=50; i++)
		p[i+50]=(int)pow(i,3);
	for(int i=1; i<=5; i++)
		scanf("%d",&a[i]);
	a[4]*=-1;
	a[5]*=-1;
	for(int i=-50; i<=50; i++) {
		if(i==0) continue;
		s[1]=a[4]*p[i+50];
		for(int j=-50; j<=50; j++) {
			if(j==0) continue;
			int ans=s[1]+a[5]*p[j+50];
			y[ans+m]++;
		}
	}
	int ans=0;
	for(int i=-50;i<=50;i++){
		if(i==0) continue;
		s[1]=a[1]*p[i+50];
		for(int j=-50;j<=50;j++){
			if(j==0) continue;
			s[2]=s[1]+a[2]*p[j+50];
			for(int k=-50;k<=50;k++){
				if(k==0) continue;
				int x=s[2]+a[3]*p[k+50];
				if(x>=-12500000&&x<=12500000)
				ans+=y[x+m];
			}
		}
	}
	printf("%d\n",ans);
	return 0;
}