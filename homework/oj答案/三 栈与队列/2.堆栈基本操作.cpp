#include<bits/stdc++.h>
using namespace std;
int main(){
	int n;cin>>n;
	vector <int> a;
	for(int i=0;i<n;i++){
		int r;cin>>r;a.push_back(r);
	}
    vector<bool> check(n + 1, false);  
    for (int i = 0; i < n; i++) {
        if (a[i] < 1 || a[i] > n || check[a[i]]) {
            cout << "NO" << endl;  
            return 0;
        }
        check[a[i]] = true;
    }
	stack<int>s;
	int popin = 1;
	bool o=1;
	vector <int> a1,a2;
	for (auto i : a){
		if(s.empty()){//要处理空栈情况
			s.push(popin);
			//cout << "PUSH "<<popin<<endl;
			a1.push_back(1);
			a2.push_back(popin);
			popin++;		
		}
		if(i>s.top()){
			while(s.top()<i){
				s.push(popin);
				//cout << "PUSH "<<popin<<endl;
				a1.push_back(1);
				a2.push_back(popin);
				popin++;
			}
		}
		if(i==s.top()){
			s.pop();
			//cout <<"POP "<<i<<endl;
			a1.push_back(0);
			a2.push_back(i);
		}
		else if(i<s.top()){
			cout<<"NO";
			o=0;
			break;
		}
	}
	if(o){
		for(int i=0;i<a1.size();i++){
			if(a1[i]==1)cout<<"PUSH ";
			else cout<<"POP ";
			cout<<a2[i]<<endl;
		}
	}
	return 0;
}
